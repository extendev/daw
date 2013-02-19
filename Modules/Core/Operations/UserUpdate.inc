<?php

/**
 * This file is part of the Daw package.
 *
 * (c) Axel Tessier <axel.tessier@extendev.net>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this module source code.
 */

namespace Daw\Modules\Core\Operations;

use \Daw\Modules\Core\Objects\User;
use \Daw\Core\Exception\OperationException;
use \Daw\Core\Exception\OperationArgumentException;

/**
 * User Update Operation
 * Update existing application user
 *
 * @package Modules/Core
 * @subpackage Operations
 * @author Axel Tessier <axel.tessier@extendev.net>
 * @version $Id: Event.inc 112 2003-08-22 06:22:40Z  $
 */
class UserUpdate extends \Daw\Core\Module\Operation {

    /**
     * Run the operation
     *
     * @param $args arguments
     * @return string response validating deletion of the site
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
