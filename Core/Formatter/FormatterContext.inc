<?php

/**
 * Application Formatters
 *
 * @package Daw
 * @subpackage Formatters
 * @author Axel Tessier <axel.tessier@extendev.net>
 * @version $Id: Event.inc 112 2003-08-22 06:22:40Z  $
 */

namespace Daw\Core\Formatter;

/**
 * Formatter context
 *
 * Context is used to store data during the formatting process
 * of a series a objects. It is composed of an hashtable where
 * values can be of any type.
 *
 * This can be used to share information
 * to the next formatters to be called to format inner objects.
 *
 * @package Daw
 * @subpackage Formatters
 * @author Axel Tessier <axel.tessier@extendev.net>
 * @version $Id: Event.inc 112 2003-08-22 06:22:40Z  $
 */
class FormatterContext {

    /**
     * @var array data stored in the context
     */
    protected $data = array();

    /**
     * Store new information in the context
     *
     * @param string $key key
     * @param object $value data
     * @return Daw\Core\Formatter\FomatterContext the formatter context
     */
    public function __set($key, $value) {
        $this->data[$key] = $value;

        return $this;
    }

    /**
     * Get context information by providing its key
     *
     * If information could not be found, the method returns null
     *
     * @param string $key key
     * @return object
     */
    public function __get($key) {
        return isset($this->data[$key]) ? $this->data[$key] : null;
    }

    /**
     * Get context information by providing its key
     *
     * If information could not be found, the method returns the default
     * value specified as argument
     *
     * @param string $key key
     * @param object $default default value
     * @return object
     */
    public function get($key, $default = null) {
        return isset($this->data[$key]) ? $this->data[$key] : $default;
    }
}
