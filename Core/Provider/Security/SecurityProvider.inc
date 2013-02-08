<?php

/**
 * This file is part of the Daw package.
 *
 * (c) Axel Tessier <axel.tessier@extendev.net>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 */

namespace Daw\Core\Provider\Security;

//require_once 'Core/provider/Provider.inc';

abstract class SecurityProvider extends \Daw\Core\Provider\Provider {

    /**
    * Return TRUE if this provider serves the specified feature
    *
    * @param string $feature
    */
    public function isProviderFor($feature) {
        return $feature === 'security';
    }

    /**
     * Perform the authentication of the user.
     * Return authenticated user if successful, or NULL otherwise.
     *
     * @param array $token
     * @return object authenticated user
     */
    public abstract function authenticate($token);

    /**
     * Check if user has access to the specified operation
     *
     * @param string $module
     * @param string $object
     * @param string $operation
     * @return boolean
     */
    public abstract function hasAccess($module, $object, $operation);
}

