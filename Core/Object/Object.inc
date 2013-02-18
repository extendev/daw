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
 * Application Object base class
 *
 * @package Daw
 * @subpackage Object
 * @author Axel Tessier <axel.tessier@extendev.net>
 * @version $Id: Event.inc 112 2003-08-22 06:22:40Z  $
 */
abstract class Object {

    /**
     * @var array $info module information as available in the Module's module.info file
     * @private
     */
    private $info = array();


    /**
     * Constructor
     *
     * @param array $info module information as available in the Module's module.info file
     */
    public function __construct($info = array()) {
        $this->info = $info;
    }

    /**
     * Return specific module information, or all module information if no name specified
     *
     * @param string $name name of the information to retrieve
     * @return mixed
     */
    public function info($name = null) {
        if ($name === null) {
            return $this->info;
        }

        return $this->info[$name];
    }

    /**
     * Return string representation of the object
     *
     * @return string
     */
    public function __toString() {
        return $this->info();
    }

    /**
     * Return name of the property to be used as primary key of the object,
     * i.e unique identifier to find an object in a store
     *
     * @return string name of the primary key
     */
    public abstract function primaryKey();

    /**
     * Magic getter to return object property based on its name, NULL if not found
     *
     * @param string $name name of the property
     * @return object property value, NULL if not found
     */
    public function __get($name) {
        if (isset($this->info[$name])) {
            return $this->info[$name];
        }

        return null;
    }

    /**
     * Magic setter for object properties
     *
     * @param string $name name of the property
     * @param object $value value to set to the property
     * @return Object the object instance
     */
    public function __set($name, $value) {
        $this->info[$name] = $value;
        return $this;
    }

    /**
     * Remove all property values
     *
     * @return Object the object instance
     */
    public function clear() {
        $this->info = array();
        return $this;
    }
}
