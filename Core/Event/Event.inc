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
 * Application Event base class
 * Not yet implemented
 *
 * @package Daw
 * @subpackage Event
 * @author Axel Tessier <axel.tessier@extendev.net>
 * @version $Id: Event.inc 112 2003-08-22 06:22:40Z  $
 */
class Event {

    /**
     * @var string $name name of the event
     */
	public final $name;

    /**
     * @var object $target object for which the target has been fired
     */
    public final $target;

    /**
     * @var array $params additional event information
     */
	public final $params;
}
