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

use \Daw\Core\Exception\OperationException;
use \Daw\Core\Exception\OperationArgumentException;

/**
 * User Deactivate Operation
 * Deactivate a user - this latter will not be able to login anymore
 * if authentication has been enabled on the security provider
 *
 * @package Modules\Core
 * @subpackage Operations
 * @author Axel Tessier <axel.tessier@extendev.net>
 * @version $Id: Event.inc 112 2003-08-22 06:22:40Z  $
 */
class UserDeactivate extends \Daw\Core\Module\Operation {

    /**
     * Run the operation
     *
     * @param $args arguments
     * @return string response validating deletion of the site
     * @see Daw\Core\Module.Operation::run()
     */
    public function run($args = array()) {
        $store = $this->module->store('user');
        if (!$store->exists($args['username'])) {
            throw new OperationException($this, 'No user exists with username: ' . $args['username'], 302);
        }

        $user = $store->read($args['username']);
        $user->active = false;
        $store->update($user);

        return 'User has been successfully deactivated';
    }
}
