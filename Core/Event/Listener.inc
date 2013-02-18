<?php

/*
 * This file is part of the Daw package.
 *
 * (c) Axel Tessier <axel.tessier@extendev.net>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 */

namespace Daw\Core\Event;

/**
 * Application Event Listener interface
 * Not yet implemented
 *
 * @package Daw
 * @subpackage Event
 * @author Axel Tessier <axel.tessier@extendev.net>
 * @version $Id: Listener.inc 112 2003-08-22 06:22:40Z  $
 */
interface Listener {

    /**
     * Callback called when an event the listener has been registered for is fired
     *
     * @param Daw\Core\event\Event event fired
     * @param string $source class origin of the event
     * @param array(string => string) params of the event
     */
    public function on($event, $source, $params);
}
