<?php

/*
 * This file is part of the Daw package.
 *
 * (c) Axel Tessier <axel.tessier@extendev.net>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 */

namespace Daw\Modules\Core\Business;

/*
 * This file is part of Daw.
 *
 * Copyright (c) 2012 Axel Tessier
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is furnished
 * to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 * @version $Id$
 */

use \Daw\Core\Core;
use \Daw\Core\Object\Store\FileStore;
use \Daw\Modules\Core\Objects\User;

/**
 * Base class for object store
 *
 * A store is eligible to
 *
 * Enter description here ...
 * @author Q.AT
 *
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


    public function map($data) {
        return new User($data);
    }

    public function unmap($user) {
        return $user->info();
    }
}
