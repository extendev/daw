<?php

/**
 * This file is part of the Daw package.
 *
 * (c) Axel Tessier <axel.tessier@extendev.net>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 */

namespace Daw\Core\Object\Store;


use \Daw\Core\Core;
use \Daw\Core\Object\Store\ObjectStore;

/**
 * Application Object Store - File
 *
 * @package Daw
 * @subpackage Object\Store
 * @author Axel Tessier <axel.tessier@extendev.net>
 * @version $Id: Event.inc 112 2003-08-22 06:22:40Z  $
 */
abstract class FileStore extends ObjectStore {

    /**
     * @var string $filepath path were all files will be stored in
     */
    protected $filepath = null;

    /**
     * @var array $store list of all objects currently present in the store
     */
    protected $store = null;

    /**
     * @var string name of the class associated to this store
     */
    protected $class = null;


    /**
     * Constructor
     *
     * @param string $file file to use to store objects
     * @param string $class name of the class of the object to store
     */
    protected function __construct($file, $class) {
        $this->filepath = Core::instance()->path($file, Core::PATH_FILES);
        $this->class = $class;
        parent::__construct();
    }

    /**
     * Initialize the store
     */
    protected function init() {
        $this->load();
    }

    /**
     * Load file contents to the store
     */
    protected function load() {
        if (file_exists($this->filepath)) {
            $contents = file_get_contents($this->filepath);
            $this->store = Core::instance()->yaml->parse($contents);
        }
    }

    /**
     * Commit any changes to the actual store support
     */
    protected function commit() {
        $contents = Core::instance()->yaml->dump($this->store);
        file_put_contents($this->filepath, $contents);
    }

    /**
     * Return an ID
     *
     * @return int
     */
    public function id() {
        return rand(100000, 10000000);
    }

    /**
     * Search store using list of given filters
     *
     * @param object $filters key/value pair list where key is the name of the filter and value its value
     * @return Object
     */
    public function search($filters = array()) {
        $criteria = array();
        if (is_array($filters)) {
            $criteria = $filters;
        } else {
            $criteria[$this->class->primaryKey()] = $filters;
        }

        $list = array();
        if (empty($this->store)) {
            return $list;
        }

        foreach ($this->store as $record) {
            if (!empty($criteria)) {
                $found = true;
                foreach ($criteria as $key => $value) {
                    if ($record[$key] != $value) {
                        $found = false;
                        break;
                    }
                }

                if ($found) {
                    $list[] = $this->map($record);
                }
            } else {
                $list[] = $this->map($record);
            }
        }

        return $list;
    }

    /**
     * Return the index of an object in the store
     *
     * @param object $object
     */
    protected function indexOf($object) {
        if (empty($this->store)) {
            return -1;
        }

        $criteria = array($this->class->primaryKey() => $object->info($this->class->primaryKey()));
        foreach ($this->store as $index => $record) {
            $found = true;
            foreach ($criteria as $key => $value) {
                if ($record[$key] != $value) {
                    $found = false;
                    break;
                }
            }

            if ($found) {
                return $index;
            }
        }

        return -1;
    }

    /**
     * Return TRUE if an object exists in the store given some filters
     *
     * @param object $filters key/value pair list where key is the name of the filter and value its value
     * @return boolean TRUE if object exists, FALSE otherwise
     */
    public function exists($filters) {
        if (empty($this->store)) {
            return false;
        }

        $criteria = array();
        if (is_array($filters)) {
            $criteria = $filters;
        } else {
            $criteria[$this->class->primaryKey()] = $filters;
        }

        foreach ($this->store as $record) {
            $found = true;
            foreach ($criteria as $key => $value) {
                if ($record[$key] != $value) {
                    $found = false;
                    break;
                }
            }

            if ($found) {
                return true;
            }
        }

        return false;
    }

    /**
     * Get a reference of an object
     *
     * @param object $filters key/value pair list where key is the name of the filter and value its value
     * @return Object
     */
    public function read($filters) {
        if (empty($this->store)) {
            return false;
        }

        $criteria = array();
        if (is_array($filters)) {
            $criteria = $filters;
        } else {
            $criteria[$this->class->primaryKey()] = $filters;
        }

        foreach ($this->store as $record) {
            $found = true;
            foreach ($criteria as $key => $value) {
                if ($record[$key] != $value) {
                    $found = false;
                    break;
                }
            }

            if ($found) {
                return $this->map($record);
            }
        }

        return false;
    }

    /**
     * Create a new object in the store
     *
     * @param Object $object
     */
    public function create($object) {
        $index = $this->indexOf($object);
        if ($index === -1) {
            $this->store[$object->info($this->class->primaryKey())] = $this->unmap($object);
        } else {
            $this->store[$index] = $this->unmap($object);
        }
        if ($this->getAutoCommit()) {
            $this->commit();
        }
    }

    /**
     * Save the object to the store
     *
     * @param Object $object
     */
    public function update($object) {
        $index = $this->indexOf($object);
        $this->store[$index] = $this->unmap($object);
        if ($this->getAutoCommit()) {
            $this->commit();
        }
    }

    /**
    * Save the object to the store
    *
    * @param Object $object
    */
    public function save($object) {
        if ($this->exists($object->info($object->primaryKey()))) {
            $this->update($object);
        } else {
            $this->create($object);
        }
    }

    /**
     * Delete an object
     *
     * @param unknown_type $object
     */
    public function delete($object) {
        $index = $this->indexOf($object);
        unset($this->store[$index]);
        if ($this->getAutoCommit()) {
            $this->commit();
        }
    }

    /**
     * Delete all objects from file store
     */
    public function clear() {
        $this->store = array();
        if ($this->getAutoCommit()) {
            $this->commit();
        }
    }

    /**
     * Map object string representation to instance of object
     * @param array $data
     * @return object object instance
     */
    protected abstract function map($data);

    /**
     * Transforms an object to a serialized string representation of the object
     * that will then be stored in the file
     *
     * @param object $object
     * @return string serialized version of the object
     */
    protected abstract function unmap($object);
}
