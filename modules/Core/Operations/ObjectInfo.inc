<?php

namespace Daw\Modules\Core\Operations;

use Daw\Core\Exception\OperationArgumentException;
use Daw\Core\Exception\Exception;

class ObjectInfo extends \Daw\Core\Module\Operation {

	/**
	* Operation execution
	*
	* @see Daw\Core\Module.Operation::run()
	*/
	public function run($args = array()) {
		$this->validate($args);

		$object = $this->core->getObject($args['name']);
		if ($object === false) {
			throw new OperationArgumentException($this, 'name', 'No object exists for given name', $args['name']);
		}

		return current($object);
	}
}
