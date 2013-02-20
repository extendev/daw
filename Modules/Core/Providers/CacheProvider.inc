<?php

/**
 * This file is part of the Daw package.
 *
 * (c) Axel Tessier <axel.tessier@extendev.net>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this module source code.
 */

namespace Daw\Modules\Core\Providers;

/**
 * Cache Provider basic implementation
 * Use simple file to store cached data
 *
 * @package Modules\Core
 * @subpackage Providers
 * @author Axel Tessier <axel.tessier@extendev.net>
 * @version $Id$
 */
class CacheProvider extends \Daw\Core\Provider\Cache\CacheProvider {

    /**
     * @var string $filename absolute path of where the cached data is stored
     */
    protected $filename = null;

    /**
     * @var array $cache cached data
     */
    protected $cache = null;


    /**
     * Initialize cache by loading the cache file and loading cached data
     *
     * @return array the cached data
     */
    protected function initCache() {
        if ($this->cache === null) {
            $config = $this->core->config('cache');
            $this->filename = $config['file'];

            $contents = file_get_contents($this->filename);
            $this->cache = $contents !== false ? unserialize($contents) : array();
        }

        return $this->cache;
    }

    /**
     * Return TRUE if a data is stored for the passed key
     *
     * @param string $key
     * @return boolean
     */
    public function contains($key) {
        $this->initCache();

        return isset($this->cache[$key]);
    }

    /**
     * Return data stored for the passed key.
     *
     * If no data exists for the given key, the method should return NULL;
     *
     * @param string $key
     * @return object
     */
    public function get($key) {
        $this->initCache();

        $value = null;
        if (isset($this->cache[$key])) {
            $value = $this->cache[$key];
        }

        return $value;
    }

    /**
     * Store data in cache and identified by the passed key
     *
     * @param string key
     * @param object data
     */
    public function add($key, $data) {
        $this->initCache();

        $this->cache[$key] = $data;

        return $this->save();
    }

    /**
     * Remove data identified by the passed key from cache
     *
     * Upon successful removal, key will not be associated with any data anymore.
     * A call to contains or get will return respectively FALSE and NULL.
     *
     * @param string key
     * @param object data
     */
    public function remove($key, $data) {
        $this->initCache();

        if (isset($this->cache[$key])) {
            unset($this->cache[$key]);
        }

        return $this->save();
    }

    /**
     * Dump cached data to the file
     *
     * @return CacheProvider the provider
     */
    protected function save() {
        $this->initCache();

        file_put_contents($this->filename, serialize($this->cache));

        return $this;
    }

    /**
     * Purge cache data
     *
     * The cache will be completely cleared, all calls to contains or get
     * will return respectively FALSE and NULL.
     */
    public function purge() {
        $this->initCache();

        $this->cache = array();

        return $this->save();
    }
}
