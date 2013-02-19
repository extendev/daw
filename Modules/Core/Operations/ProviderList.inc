<?php

/**
 * This file is part of the Daw package.
 *
 * (c) Axel Tessier <axel.tessier@extendev.net>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this module source code.
 */

namespace Daw\Modules\Core\Operations;

/**
 * Provider List Operation
 * Return list of providers registered by modules
 *
 * @package Modules/Core
 * @subpackage Operations
 * @author Axel Tessier <axel.tessier@extendev.net>
 * @version $Id: Event.inc 112 2003-08-22 06:22:40Z  $
 */
class ProviderList extends \Daw\Core\Module\Operation {

    /**
     * Run the operation
     *
     * @param $args arguments
     * @return string response validating deletion of the site
     * @see Daw\Core\Module.Operation::run()
     */
    public function run($args = array()) {
        $list = array();

        foreach ($this->core->getProviders() as $feature => $providers) {
            $list[$feature] = array(
                'default' => null,
                'available' => array(),
                'config' => $this->core->config($feature)
            );

            foreach ($providers as $provider) {
                $list[$feature]['available'][] = get_class($provider);
            }

            $list[$feature]['default'] = get_class($this->core->$feature);
        }

        return $list;
    }
}
