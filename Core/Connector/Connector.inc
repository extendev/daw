<?php

/*
 * This file is part of the Daw package.
 *
 * (c) Axel Tessier <axel.tessier@extendev.net>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 */

namespace namespace Daw\Core\Connector;

/**
 * Application Connector interface
 *
 * Access to external applications shall be implemented through connectors.
 * These latter have to implement this interface to be recognized by the
 * application as a valid connector.
 *
 * A connector is free to implement the methods required to access and
 * communicate with the application.
 *
 * @package Daw
 * @subpackage Connector
 * @author Axel Tessier <axel.tessier@extendev.net>
 * @version $Id$
 */
interface Connector {
}
