<?php

/*
 * This file is part of the Daw package.
 *
 * (c) Axel Tessier <axel.tessier@extendev.net>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 */

/**
 * Hub core includes
 */

define('MODULE_PATH', realpath(PROJECT_BASEPATH . '/Modules'));
define('PROVIDER_PATH', realpath(PROJECT_BASEPATH . '/Providers'));
/* 
  TO BE GRUIKED AGAIN ??
define('FORMATERS_PATH', realpath(PROJECT_BASEPATH . '/Formaters'));
define('PROVIDER_PATH', realpath(PROJECT_BASEPATH . '/Providers'));
*/

// Core includes
require_once 'Core/Core.inc';
require_once 'Core/Exception/Exception.inc';

require_once 'vendor/autoload.php';
