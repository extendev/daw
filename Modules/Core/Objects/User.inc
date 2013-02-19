<?php

/**
 * This file is part of the Daw package.
 *
 * (c) Axel Tessier <axel.tessier@extendev.net>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 */

namespace Daw\Modules\Core\Objects;

class User extends \Daw\Core\Object\Object  {

    protected $name;
    protected $username;
    protected $password;
    protected $email;
    protected $active;

    public function primaryKey() {
        return 'username';
    }
}
