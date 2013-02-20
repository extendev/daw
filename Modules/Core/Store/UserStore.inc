<?php

/**
 * This file is part of the Daw package.
 *
 * (c) Axel Tessier <axel.tessier@extendev.net>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 */

namespace Daw\Modules\Core\Store;

use \Daw\Core\Core;
use \Daw\Modules\Core\Store\FileStore;
use \Daw\Modules\Core\Objects\User;

/**
 * Store for managing Daw application users
 * This store is a FileStore using file users.db to store users
 *
 * @package Modules\Core
 * @subpackage Store
 * @author Axel Tessier <axel.tessier@extendev.net>
 * @version $Id: Event.inc 112 2003-08-22 06:22:40Z  $
 */
class UserStore extends FileStore {

    /**
     * Get shared instance of user store
     *
     * @return UserStore
     */
    public static function instance() {
        static $instance = null;
        if ($instance === null) {
            $instance = new UserStore('users.db', new User());
        }

        return $instance;
    }

    /**
     * Initialize the store
     *
     * When loaded for the first time, we take the list of users
     * defined in security provider configuration
     */
    protected function init() {
        parent::init();

        if ($this->store === null) {
            $config = Core::instance()->config('security');
            $this->store = $config['users'];
            $this->commit();
        }
    }

    /**
     * Map string representation to User instance
     *
     * @param array $data
     * @return User object instance
     */
    public function map($data) {
        return new User($data);
    }

    /**
     * Transforms a User object to a serialized string representation
     *
     * @param User $object
     * @return string serialized version of the object
     */
    public function unmap($object) {
        return $object->info();
    }
}
