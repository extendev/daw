<?php

/*
 * This file is part of the Daw package.
 *
 * (c) Axel Tessier <axel.tessier@extendev.net>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 */

namespace Daw\Core\Object;

/**
 * Application Object Store base class
 *
 * A store is eligible to perform any CRUD operations
 * on object and for a given storage type
 *
 * @package Daw
 * @subpackage Object
 * @author Axel Tessier <axel.tessier@extendev.net>
 * @version $Id: Event.inc 112 2003-08-22 06:22:40Z  $
 */
abstract class Store {

    /**
     * AutoCommit mode
     *
     * By default, auto commit is enabled, meaning that
     * every CRUD action will be directly commited to the store
     *
     * @var boolean
     */
    protected $autoCommit = true;

    protected $store = null;

    /**
     * Constructor
     */
    protected function __construct() {
        $this->init();
    }

    /**
     * Initialize the store
     */
    protected function init() {
    }

    /**
     * Search
     *
     * @param object $id
     * @return Object
     */
    public abstract function search($params = null);

    /**
     * Check if an object exists
     *
     * @param unknown_type $object
     */
    public abstract function exists($object);

    /**
    * Get a reference of an object
    *
    * @param object $id
    * @return Object
    */
    public abstract function read($id);

    /**
     * Create a new object in the store
     *
     * @param Object $object
     */
    public abstract function create($object);

    /**
     * Update an object and store it in the store
     * @param unknown_type $object
     */
    public abstract function update($object);

    /**
    * Save the object to the store
    *
    * @param Object $object
    */
    public abstract function save($object);

    /**
     * Delete an object
     *
     * @param unknown_type $object
     */
    public abstract function delete($object);

    /**
     * Delete all objects
     */
    public abstract function clear();

    /**
     * Set auto commit mode
     *
     * @param boolean $flag
     */
    public function setAutoCommit($flag = true) {
        $this->autoCommit = $flag;
    }

    /**
     * Return auto commit mode valud
     *
     * @return boolean
     */
    public function getAutoCommit() {
        return $this->autoCommit;
    }

}
