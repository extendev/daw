<?php

namespace Daw\Modules\Core\Operations;

use \Daw\Core\Exception\Exception;

class ModuleInfo extends \Daw\Core\Module\Operation {

	/**
	 * Operation execution
	 *
	 * @see Daw\Core\Module.Operation::run()
	 */
	public function run($args = array()) {
		if (!isset($args['name'])) {
			throw new Exception('Module name is required', 301);
		}

		$module = $this->core->getModule($args['name']);
		if ($module === false) {
			throw new Exception('Module could not be found', 302);
		}

		return $module->info();
	}
}
