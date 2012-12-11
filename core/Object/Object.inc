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

    private $info = array();

    public function __construct($info = array()) {
        $this->info = $info;
    }

    /**
    * Return module information
    */
    public function info($value = null) {
        if ($value === null) {
            return $this->info;
        }

        return $this->info[$value];
    }

    public function __toString() {
        return $this->info();
    }


    public abstract function primaryKey();

    public function __get($key) {
    	if (isset($this->info[$key])) {
    		return $this->info[$key];
    	}
    	return null;
    }

    public function __set($key, $value) {
    	$this->info[$key] = $value;
    	return $this;
    }

    public function clear() {
    	$this->info = array();
    }
}