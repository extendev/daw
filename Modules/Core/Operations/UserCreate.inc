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
use \Daw\Core\Exception\OperationArgumentException;

/**
 * User Create Operation
 * Create a new application user
 *
 * @package Modules\Core
 * @subpackage Operations
 * @author Axel Tessier <axel.tessier@extendev.net>
 * @version $Id: Event.inc 112 2003-08-22 06:22:40Z  $
 */
class UserCreate extends \Daw\Core\Module\Operation {

    /**
     * Run the operation
     *
     * @param $args arguments
     * @return string response validating deletion of the site
     * @see Daw\Core\Module.Operation::run()
     */
    public function run($args = array()) {

        $store = $this->module->store('user');

        $user = new User();
        $user->name = $args['name'];
        $user->username = $args['username'];
        $user->password = $this->module->cryptPassword($args['password']);
        $user->email = $args['email'];
        $user->active = $args['active'] === 'true';
        $store->create($user);

        return $user->info();
    }
}
