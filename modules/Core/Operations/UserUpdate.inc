<?php

namespace Daw\Modules\Core\Operations;

use Daw\Modules\Core\Objects\User;
use Daw\Core\Exception\OperationException;
use Daw\Core\Exception\OperationArgumentException;

/**
 * Operation: User Update
 *
 * @author Q.AT
 * @version $Id$
 */
class UserUpdate extends \Daw\Core\Module\Operation {

	/**
	 * Operation execution
	 *
	 * @see Daw\Core\Module.Operation::run()
	 */
	public function run($args = array()) {
		$store = $this->module->store('user');
		if (!$store->exists($args['user'])) {
			throw new OperationException($this, 'No user exists with username: ' . $args['user'], 302);
		}

		$user = $store->read($args['user']);
		if (isset($args['username'])) {
			$user->username = $args['username'];
		}
		if (isset($args['name'])) {
			$user->name = $args['name'];
		}
		if (isset($args['password'])) {
			$user->password = $args['password'];
		}
		if (isset($args['email'])) {
			$user->email = $args['email'];
		}
		if (isset($args['active'])) {
			$user->active = $args['active'];
		}
		$store->update($user);

		return $store->unmap($user);
	}
}
