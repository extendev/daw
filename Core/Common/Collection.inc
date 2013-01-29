<?php

/*
 * This file is part of the Daw package.
 *
 * (c) Axel Tessier <axel.tessier@extendev.net>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 */

namespace Daw\Core\Common;

/**
 * Application Common Utils - Collection base class
 *
 * Not yet implemented
 *
 * Collection that can be used to run methods on all objects of the collection
 *
 *  $list = New Collection($obj1, $obj2, $obj3)
 *  $list->delete(); // will call delete methods for all 3 objects
 *
 * @package Daw
 * @subpackage Common
 * @author Axel Tessier <axel.tessier@extendev.net>
 * @version $Id$
 */
class Collection {

	/**
	 * Return first object of the collection
	 *
 	 * Not yet implemented
	 */
	public function first() {

	}

	/**
	 * Return last object of the collection
	 *
 	 * Not yet implemented
	 */
	public function all() {

	}

	/**
	 * Call specified function on all objects of the collection
	 *
 	 * Not yet implemented
 	 *
 	 * @param function $function function to call on all objects on the collection
	 */
	public function apply($function) {

	}
}
