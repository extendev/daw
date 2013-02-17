<?php

/**
 * This file is part of the Daw package.
 *
 * (c) Axel Tessier <axel.tessier@extendev.net>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 */

namespace Daw\Core\Object;

/**
 * Application Object - Module
 *
 * @package Daw
 * @subpackage Object
 * @author Axel Tessier <axel.tessier@extendev.net>
 * @version $Id: Event.inc 112 2003-08-22 06:22:40Z  $
 */
class Module {

    /**
     * @var array $info module information as available in the Module's module.info file
     * @private
     */
    private $info = array();


    /**
     * Constructor
     *
     * @param array $info module information as available in the Module's module.info file
     */
    public function __construct($info = array()) {
        $this->info = $info;
    }

    /**
     * Return specific module information, or whole list if no config name has been specified
     *
     * @param string $name name of the informatio
     * @return mixed
     */
    public function info($name = null) {
        if ($name === null) {
            return $this->info;
        }

        return $this->info[$name];
    }
}
