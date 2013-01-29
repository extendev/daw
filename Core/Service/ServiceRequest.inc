<?php

/*
 * This file is part of the Daw package.
 *
 * (c) Axel Tessier <axel.tessier@extendev.net>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 */

namespace Daw\Core\Service;

abstract class ServiceRequest {
	public $date;
	public $args = array();

	public function __construct() {
		$this->date = time();
	}

	/**
	 * Return list of arguments passed to the service and to be used by the module call
	 *
	 * @return array
	 */
	public abstract function getArgs();

	/**
	 * Provides information related to the user authentication
	 *
	 * @return array
	 */
	public abstract function getAuthenticationToken();
}
