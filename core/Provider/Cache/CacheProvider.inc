<?php

namespace Daw\Core\Provider\Cache;

abstract class CacheProvider extends \Daw\Core\Provider\Provider {

	/**
	* Return TRUE if this provider serves the specified feature
	*
	* @param string $feature
	*/
	public function isProviderFor($feature) {
		return $feature === 'cache';
	}

	public abstract function contains($key);
	public abstract function get($key);
	public abstract function add($key, $data);
	public abstract function remove($key, $data);
	public abstract function purge();
}

