<?php

namespace Daw\Modules\Core\Operations;

use \Daw\Core\Exception\OperationException;
use \Daw\Core\Exception\OperationArgumentException;

/**
 * Operation: User Add
 *
 * @author Q.AT
 * @version $Id$
 */
class UserActivate extends \Daw\Core\Module\Operation {

    /**
     * Operation execution
     *
     * @see Daw\Core\Module.Operation::run()
     */
    public function run($args = array()) {
        $store = $this->module->store('user');
        if (!$store->exists($args['username'])) {
            throw new OperationException($this, 'No user exists with username: ' . $args['username'], 302);
        }

        $user = $store->read($args['username']);
        $user->active = true;
        $store->update($user);

        return 'User has been successfully activated';
    }
}
