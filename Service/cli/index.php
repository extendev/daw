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
 * CLI Service Entry Point
 * Any command line command will be processed through this file
 *
 * @package daw
 * @author Axel Tessier <axel.tessier@extendev.net>
 * @version $Id: index.php 106 2003-08-22 01:24:18Z  $
 */

/**
* Project base directory for CLI service
*
* @var string
*/
define('PROJECT_BASEPATH', realpath(__DIR__. '/../../../'));

require_once 'Service/includes.inc';

use Daw\Core\Service\CliService;

$service = new CliService();
\Daw\Core\Core()->start($service);
