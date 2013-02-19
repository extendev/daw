<?php

/**
 * This file is part of the Daw package.
 *
 * (c) Axel Tessier <axel.tessier@extendev.net>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 */

namespace Daw\Modules\Core;

use \Daw\Modules\Core\Store\UserStore;

/**
 * Daw Module: Core Application Module
 *
 * This module provides the basic features of the Daw application
 * like information collection on modules, objects, operations, ...
 *
 * @package Modules
 * @subpackage Core
 * @author Axel Tessier <axel.tessier@extendev.net>
 * @version $Id: Event.inc 112 2003-08-22 06:22:40Z  $
 */
class Module extends \Daw\Core\Module\Module {

    /**
     * Return store for a given object
     *
     * @param string $name object name
     * @return ObjectStore the store if found, NULL otherwise
     */
    public function store($name) {
        switch ($name) {
            case 'user':
                return UserStore::instance();
                break;
        }

        return null;
    }

}
