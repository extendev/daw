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
 * Operation object
 *
 * @package Daw
 * @subpackage Object
 * @author Axel Tessier <axel.tessier@extendev.net>
 * @version $Id: Event.inc 112 2003-08-22 06:22:40Z  $
 */
class Operation {

    /**
     * @var string $name name of the operation
     */
    private $name = null;

    /**
     * @var array $info operation information as available in the Module's module.info file
     * @private
     */
    private $info = array();


    /**
     * Constructor
     *
     * @param string $name name of the operation
     * @param array $info module information as available in the Module's module.info file
     */
    public function __construct($name, $info = array()) {
        $this->name = $name;
        $this->info = $info;
    }

    /**
     * Return operation name in parent module
     */
    public function getName() {
        return $this->name;
    }

    /**
     * Return specific operation information, or all information if no name specified
     *
     * @param string $name name of the information to retrieve
     * @return mixed
     */
    public function info($name = null) {
        if ($name === null) {
            return $this->info;
        }

        return $this->info[$name];
    }
}
