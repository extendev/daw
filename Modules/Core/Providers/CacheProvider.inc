<?php

/**
 * This file is part of the Daw package.
 *
 * (c) Axel Tessier <axel.tessier@extendev.net>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 */

namespace Daw\Modules\Core\Providers;

/**
 * Cache provider using files
 *
 */
class CacheProvider extends \Daw\Core\Provider\Cache\CacheProvider {

    protected $filename = null;
    protected $cache = null;

    protected function initCache() {
        if ($this->cache === null) {
            $config = $this->core->config('cache');
            $this->filename = $config['file'];

            $contents = file_get_contents($this->filename);
            $this->cache = $contents !== false ? unserialize($contents) : array();
        }

        return $this->cache;
    }

    public function contains($key) {
        $this->initCache();

        return isset($this->cache[$key]);
    }

    public function get($key) {
        $this->initCache();

        $value = null;
        if (isset($this->cache[$key])) {
            $value = $this->cache[$key];
        }

        return $value;
    }

    public function add($key, $data) {
        $this->initCache();

        $this->cache[$key] = $data;

        return $this->save();
    }

    public function remove($key, $data) {
        $this->initCache();

        if (isset($this->cache[$key])) {
            unset($this->cache[$key]);
        }

        return $this->save();
    }

    protected function save() {
        $this->initCache();

        file_put_contents($this->filename, serialize($this->cache));

        return $this;
    }

    public function purge() {
        $this->initCache();

        $this->cache = array();

        return $this->save();
    }
}
