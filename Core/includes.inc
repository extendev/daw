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

define('MODULE_PATH', realpath(PROJECT_BASEPATH . '/modules'));
define('PROVIDER_PATH', realpath(PROJECT_BASEPATH . '/providers'));

// Core includes
require_once 'Core/Core.inc';
require_once 'Core/business/AutoLoader.inc';
require_once 'Core/exception/Exception.inc';

// Load default providers
//require_once PROVIDER_PATH . '/includes.inc';
require_once 'vendor/autoload.php';
