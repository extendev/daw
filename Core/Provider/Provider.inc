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

abstract class Provider {

    protected $core = null;
    protected $module = null;


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
