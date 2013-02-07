<?php

namespace Daw\Modules\Core\Operations;

use \Daw\Modules\Core\Objects\User;
use \Daw\Core\Exception\OperationArgumentException;

/**
 * Operation: User Create
 *
 * @author Q.AT
 * @version $Id$
 */
class UserCreate extends \Daw\Core\Module\Operation {

    /**
     * Operation execution
     *
     * @see Daw\Core\Module.Operation::run()
     */
    public function run($args = array()) {

        $store = $this->module->store('user');

        $user = new User();
        $user->name = $args['name'];
        $user->username = $args['username'];
        $user->password = $args['password'];
        $user->email = $args['email'];
        $user->active = $args['active'] === 'true';
        $store->create($user);

        return $user->info();
    }
}
