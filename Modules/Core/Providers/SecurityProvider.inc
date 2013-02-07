<?php

namespace Daw\Modules\Core\Providers;

use \Daw\Core\Provider\Security\Exception\AuthenticationException;

/**
 * Base security provider
 * Use users managed by core module
 *
 * @author Q.AT
 *
 */
class SecurityProvider extends \Daw\Core\Provider\Security\SecurityProvider {

    private $user = null;

    public function user() {
        return $this->user;
    }

    /**
     * Perform the authentication of the user.
     * Return authenticated used if successful, or NULL otherwise.
     *
     * @param array $token
     * @return object authenticated user
     */
    public function authenticate($token) {
        $user = false;

        // Authenticate user only if authentication is enabled
        $config = $this->core->config('security');
        if (!isset($config['authentication'])
            || !isset($config['authentication']['enable'])
            || $config['authentication']['enable'] === true) {

            $username = isset($token['username']) ? $token['username'] : null;
            $password = isset($token['password']) ? $token['password'] : null;

            // We check that a username has been specified.
            // If not, then we'll continue with no user set
            if ($username) {

                // Verify that user exist
                $userList = $this->core->sudo('user', 'list');
                if (!isset($userList[$username])) {
                    throw new AuthenticationException('User does not exist', 401);
                }

                if (isset($config['authentication']) && isset($config['authentication']['blacklist'])) {
                    $blacklistedUsers = explode(' ', $config['authentication']['blacklist']);
                    if (in_array($username, $blacklistedUsers)) {
                        throw new AuthenticationException('User has been blacklisted.', 403);
                    }
                }

                $user = $userList[$username];

                // And that password matches
                if ($user['password'] != $password) {
                    throw new AuthenticationException('Password does not match', 401);
                }
            }
        }

        $this->user = $user;

        return $this->user();
    }

    /**
     * Check if user has access to the specified operation
     *
     * @param string $module
     * @param string $object
     * @param string $operation
     */
    public function hasAccess($module, $object, $operation) {
        $this->core->log->debug(__NAMESPACE__ . "hasAccess($module, $object, $operation)");
        $config = $this->core->config('security');

        $user = $this->user();
        $username = isset($user['username']) ? $user['username'] : false;
        $object = $object != null ? $object : $module;
        $accessConfig = $config['access'];
        $defaultAccess = isset($accessConfig['default']) ? $accessConfig['default'] : 'allow';
        $this->core->log->trace(__NAMESPACE__ . " default access = $defaultAccess.");

        // Check operations access level permissions
        if (!isset($accessConfig['operations'])) {
            return true;
        }

        foreach ($accessConfig['operations'] as $op => $opInfo) {

            $operationSubject = $op;
            $operationName = null;

            $operationSeparatorPos = strpos($op, '.');
            if ($operationSeparatorPos !== false) {
                $operationSubject = substr($op, 0, $operationSeparatorPos);
                $operationName = substr($op, $operationSeparatorPos + 1);
            }

            $this->core->log->trace(__NAMESPACE__ . " test entry $operationSubject / $operationName.");
            if ($object == $operationSubject
                && ($operationName === null || $operationName == $operation || $operationName == '*')) {
                $operationDefaultAccess = isset($opInfo['default']) ? $opInfo['default'] : $defaultAccess;
                if ($operationDefaultAccess === 'allow') {
                    if (isset($opInfo['deny'])) {
                        $deniedUsers = explode(' ', $opInfo['deny']);
                        if (in_array('all', $deniedUsers)
                                || in_array($username, $deniedUsers)) {
                            $this->core->log->trace(__NAMESPACE__ . " user in entry denied users: " . $opInfo['deny'] . ".");
                            return false;
                        }
                    }

                    $this->core->log->trace(__NAMESPACE__ . " using operation default access : $operationDefaultAccess.");
                    return true;
                } else {
                    if (isset($opInfo['allow'])) {
                        $allowedUsers = explode(' ', $opInfo['allow']);
                        if (in_array('all', $allowedUsers)
                            || in_array($username, $allowedUsers)) {
                            $this->core->log->trace(__NAMESPACE__ . " user in entry allowed users: " . $opInfo['allow'] . ".");
                            return true;
                        }
                    }

                    $this->core->log->trace(__NAMESPACE__ . " using operation default access : $operationDefaultAccess.");
                    return false;
                }
            }
        }

        return true;
    }
}
