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

/**
 * User object class
 *
 * @package Modules\Core
 * @subpackage Objects
 * @author Axel Tessier <axel.tessier@extendev.net>
 * @version $Id$
 */
class User extends \Daw\Core\Object\Object  {

    /**
     * @var string $name user full name
     */
    protected $name;
    /**
     * @var string $username user login
     */
    protected $username;
    /**
     * @var string $password user password
     */
    protected $password;
    /**
     * @var string $email user email address
     */
    protected $email;
    /**
     * @var boolean user active status
     */
    protected $active;

    /**
     * Return name of the property to be used as primary key of the object,
     * i.e unique identifier to find an object in a store.
     *
     * For User object, returns 'username'
     *
     * @return string name of the primary key
     */
    public function primaryKey() {
        return 'username';
    }
}
