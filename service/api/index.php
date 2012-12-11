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
 * API Service Entry Point
 * Any service has to include this file to work properly.
 *
 * @package daw
 * @author Axel Tessier <axel.tessier@extendev.net>
 * @version $Id: index.php 106 2003-08-22 01:24:18Z  $
 */

/**
* Project base directory for API service
*
* @var string
*/
define('PROJECT_BASEPATH', realpath(getcwd() . '/../../../'));

require_once 'service/includes.inc';
require_once 'core/service/ApiService.inc';

$service = new ApiService();
\daw\Core\core()->start($service);
