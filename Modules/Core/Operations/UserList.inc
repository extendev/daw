<?php

namespace Daw\Modules\Core\Operations;

use \Daw\Modules\Core\Objects\User;

/**
 * Operation: User List
 *
 * @author Q.AT
 * @version $Id$
 */
class UserList extends \Daw\Core\Module\Operation {

    public function run($args = array()) {
        $list = array();
        foreach ($this->module->store('user')->search() as $user) {
            $list[$user->username] = $user->info();
        }

        return $list;
    }
}
