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

/**
 * Provider base class
 *
 * @package Daw
 * @subpackage Provider
 * @author Axel Tessier <axel.tessier@extendev.net>
 * @version $Id$
 */
abstract class Provider {

    /**
     * @var Core $core daw instance
     */
    protected $core = null;

    /**
     * @var Module parent module instance
     */
    protected $module = null;

    /**
     * Constructor
     * @param Core $core daw instance
     * @param Module $module parent module
     */
    public function __construct($core, $module = null) {
        $this->core = $core;
        $this->module = $module;
    }

    /**
     * Return parent module
     *
     * @return \Daw\Core\Module\Module
     */
    public function getModule() {
        return $this->module;
    }

    /**
     * Return TRUE if this provider serves the specified feature
     *
     * @param string $feature
     */
    public abstract function isProviderFor($feature);
}
