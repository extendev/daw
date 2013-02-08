<?php

/**
 * This file is part of the Daw package.
 *
 * (c) Axel Tessier <axel.tessier@extendev.net>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 */

/**
 * SplAutoLoader for Daw project
 *
 * @package Daw
 * @author Axel Tessier <axel.tessier@extendev.net>
 * @version $Id$
 */

/**
 * spl_autoload() suitable implementation for supporting class autoloading.
 * Comply with PSR-0 implementation
 *
 * @link https://github.com/php-fig/fig-standards/blob/master/accepted/PSR-0.md
 * @param string $class the class to load
 * @return string|false Class name on success; false on failure
 */
function coreAutoLoad($class) {

    $classTokens = explode('\\', $class);
    switch (array_shift($classTokens)) {
        case 'Daw':
            switch ($classTokens[0]) {
                case 'Modules':
                    $classNS = join('/', array_slice($classTokens, 1));
                    require_once MODULE_PATH . '/' . $classNS . '.inc';
                    break;
                default:
                    $classNS = join('/', $classTokens);
                    require_once $classNS . '.inc';
                    break;
            }
            break;
    }
}

// Class autoloader
spl_autoload_register('coreAutoLoad');
