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
 * Application Event Controller
 * Not yet implemented
 *
 * @package Daw
 * @subpackage Event
 * @author Axel Tessier <axel.tessier@extendev.net>
 * @version $Id: EventController.inc 112 2003-08-22 06:22:40Z  $
 */
class EventController {

    /**
     * Register a listener against an event and with possible filters
     *
     * @param Daw\Core\event\Listener listener to register
     * @param string $event name of the event
     * @param string[] filters
     */
    public function registerListener($listener, $event, $filters = array()) {
    }

    /**
     * Fire an event to the application
     *
     * @param Daw\Core\event\Event event to fire
     * @param string $source class origin of the event
     * @param array(string => string) params of the event
     */
    public function fireEvent($name, $source, $params = array()) {
    }
}
