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

use \Daw\Core\Service\ServiceRequest;

class CliServiceRequest extends ServiceRequest {

	public function getProperties() {
		return $_SERVER;
	}

	public function getArgs() {
		$args = array();
		$nbArgs =  $_SERVER['argc'];

		if ($nbArgs > 1) {
			$args['OBJECT'] = $_SERVER['argv'][1];
		}
		if ($nbArgs > 2) {
			$args['OPERATION'] = $_SERVER['argv'][2];
		}

		$args['PARAMS'] = array();
		if ($nbArgs > 3) {
			foreach (array_slice($_SERVER['argv'], 2) as $arg) {
				if (strpos($arg, '=') === false) {
					$args['PARAMS'][$arg] = true;
				} else {
					$args['PARAMS'][substr($arg, 0, strpos($arg, '='))] = substr($arg, strpos($arg, '=') + 1);
				}
			}
		}

		return $args;
	}

	public function getAuthenticationToken() {
		$token = array();
		if (isset($_SERVER['Daw_USERNAME'])) {
			$token['username'] = $_SERVER['Daw_USERNAME'];
		}
		if (isset($_SERVER['Daw_PASSWORD'])) {
			$token['password'] = $_SERVER['Daw_PASSWORD'];
		}

		return $token;
	}
}
