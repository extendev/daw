<?php

/*
 * This file is part of the Daw package.
 *
 * (c) Axel Tessier <axel.tessier@extendev.net>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 */

namespace Daw\Modules\Core;

use \Daw\Modules\Core\Business\UserStore;

/**
 * Daw Module: Core Application Module
 *
 * This module provides the basic features of the Daw application
 * like information collection on modules, objects, operations, ...
 *
 * @author Q.AT
 */
class Module extends \Daw\Core\Module\Module {

    /**
     * Return store
     *
     * @param ObjectStore $name
     */
    public function store($name) {
        switch ($name) {
            case 'user':
                return UserStore::instance();
                break;
        }
    }

}
