<?php

namespace Daw\Core\Provider;

require_once 'Provider.inc';

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
