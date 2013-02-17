<?php

/**
 * This file is part of the Daw package.
 *
 * (c) Axel Tessier <axel.tessier@extendev.net>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 */

namespace Daw\Core\Provider\Cache;

/**
 * Cache Provider base abstract class
 * Extends this class if you wish to implement your own cache provider
 *
 * @package Daw
 * @subpackage Provider
 * @author Axel Tessier <axel.tessier@extendev.net>
 * @version $Id$
 */
abstract class CacheProvider extends \Daw\Core\Provider\Provider {

  /**
   * Return TRUE if this provider serves the specified feature
   *
   * @param string $feature
   */
  public function isProviderFor($feature) {
    return $feature === 'cache';
  }

  /**
   * Return TRUE if a data is stored for the passed key
   *
   * @param string $key
   * @return boolean
   */
  public abstract function contains($key);

  /**
   * Return data stored for the passed key.
   *
   * If no data exists for the given key, the method should return NULL;
   *
   * @param string $key
   * @return object
   */
  public abstract function get($key);

  /**
   * Store data in cache and identified by the passed key
   *
   * @param string key
   * @param object data
   */
  public abstract function add($key, $data);

  /**
   * Remove data identified by the passed key from cache
   *
   * Upon successful removal, key will not be associated with any data anymore.
   * A call to contains or get will return respectively FALSE and NULL.
   *
   * @param string key
   * @param object data
   */
  public abstract function remove($key, $data);

  /**
   * Purge cache data
   *
   * The cache will be completely cleared, all calls to contains or get
   * will return respectively FALSE and NULL.
   */
  public abstract function purge();
}

