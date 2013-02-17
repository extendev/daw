<?php

/**
 * This file is part of the Daw package.
 *
 * (c) Axel Tessier <axel.tessier@extendev.net>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 */

namespace Daw\Core\Provider;

require_once 'Provider.inc';

/**
 * Null Provider class - does nothing
 *
 * @package Daw
 * @subpackage Provider
 * @author Axel Tessier <axel.tessier@extendev.net>
 * @version $Id$
 */
class NullProvider extends \Daw\Core\Provider\Provider {

    /**
     * Return TRUE if this provider serves the specified feature
     *
     * @param string $feature
     */
    public function isProviderFor($feature) {
        return TRUE;
    }

    /**
     * Magic call method to call to any methods
     *
     * @param string $name
     * @param array $arguments
     */
    public function __call($name, $arguments) {
    }

    /**
    * Magic getter
    *
    * @param string $name
    */
    public function __get($name) {
        return null;
    }

    /**
    * Magic setter
    *
    * @param string $name
    * @param mixed $value
    */
    public function __set($name, $value) {
    }
}
