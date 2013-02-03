<?php

namespace Daw\Core\Provider\Security;

//require_once 'core/provider/Provider.inc';

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
     * Return authenticated used if successful, or NULL otherwise.
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
	 */
	public abstract function hasAccess($module, $object, $operation);
}

