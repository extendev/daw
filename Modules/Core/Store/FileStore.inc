<?php

/**
 * This file is part of the Daw package.
 *
 * (c) Axel Tessier <axel.tessier@extendev.net>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 */

namespace Daw\Modules\Core\Store;

use \Daw\Core\Core;
use \Daw\Core\Object\Store;

/**
 * Application Object Store - File
 *
 * @package Core
 * @subpackage Store
 * @author Axel Tessier <axel.tessier@extendev.net>
 * @version $Id: Event.inc 112 2003-08-22 06:22:40Z  $
 */
abstract class FileStore extends Store {

  /**
   * @var string $filepath path of the file where to store objects
   */
  protected $filepath = null;
  /**
   * @var array store contents
   */
  protected $store = null;
  /**
   * @var Object $instance an instance of the object to manage in the store
   */
  protected $instance = null;


  /**
   * Constructor
   *
   * @param string $file file path where objects will be stored
   * @param Object $instance an instance of the object to manage in the store
   */
  protected function __construct($file, $instance) {
    $this->filepath = Core::instance()->path($file, Core::PATH_FILES);
    $this->instance = $instance;
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
   */
  public function id() {
    return rand(100000, 10000000);
  }

  /**
   * Search objects and return those matching list of search params
   *
   * @param object $params
   * @return array list of objects matching the search params
   */
  public function search($params = array()) {
    $criteria = array();
    if (is_array($params)) {
      $criteria = $params;
    } else {
      $criteria[$this->instance->primaryKey()] = $params;
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
   * @param mixed $object the object to find
   * @return int the index if found, -1 otherwise
   */
  protected function indexOf($object) {
    if (empty($this->store)) {
      return -1;
    }

    $criteria = array($this->instance->primaryKey() => $object->info($this->instance->primaryKey()));
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
   * Check if an object exists
   *
   * @param mixed $params
   * @return boolean
   */
  public function exists($params) {
    if (empty($this->store)) {
      return false;
    }

    $criteria = array();
    if (is_array($params)) {
      $criteria = $params;
    } else {
      $criteria[$this->instance->primaryKey()] = $params;
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
   * Get a reference of an object given filters
   *
   * @param array $params
   * @return Object
   */
  public function read($params) {
    if (empty($this->store)) {
      return false;
    }

    $criteria = array();
    if (is_array($params)) {
      $criteria = $params;
    } else {
      $criteria[$this->instance->primaryKey()] = $params;
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
      $this->store[$object->info($this->instance->primaryKey())] = $this->unmap($object);
    } else {
      $this->store[$index] = $this->unmap($object);
    }
    if ($this->getAutoCommit()) {
      $this->commit();
    }
  }

  /**
   * Update an object and store it in the store
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
   * Delete an object from the store
   *
   * @param Object $object
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
