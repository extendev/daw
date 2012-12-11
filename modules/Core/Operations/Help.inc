<?php

namespace Daw\Modules\Core\Operations;

class Help extends \Daw\Core\Module\Operation {

	public function run($args = array()) {
		return array(
			'message' => 'You\'ve just reached Daw core module. This means the application is working properly',
			'usage' => 'Use this module to get general information about objects, operations available on the application'
		);
	}
}
