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
 * HTTP Service Entry Point
 * Any HTTP service request will be processed through this file
 * The home.html file defines the UI used to access the HTTP service
 *
 * @package daw
 * @see home.html
 * @author Axel Tessier <axel.tessier@extendev.net>
 * @version $Id: index.php 106 2003-08-22 01:24:18Z  $
 */

/**
* Project base directory for HTTP service
*
* @var string
*/
define('PROJECT_BASEPATH', realpath(getcwd() . '/../../'));

require_once 'Service/includes.inc';

use Daw\Core\Service\HttpService;

if ($_SERVER['REQUEST_URI'] === '/') {
    print file_get_contents(getcwd() . '/home.html');
    exit();
}

$service = new HttpService();
\Daw\Core\Core()->start($service);
