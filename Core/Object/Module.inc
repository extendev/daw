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

    private $info = array();

    public function __construct($info = array()) {
        $this->info = $info;
    }

    /**
    * Return module information
    */
    public function info($value = null) {
        if ($value === null) {
            return $this->info;
        }

        return $this->info[$value];
    }
}
