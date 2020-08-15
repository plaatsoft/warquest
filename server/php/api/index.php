<?php

// WarQuest JSON REST API for WarQuest Android App
// Made by Bastiaan van der Plaat

// Simple router
class Router {
    // A wrapper function to match a get route
    public static function get ($route, $callback) {
        static::match(['get'], $route, $callback);
    }

    // A wrapper function to match a post route
    public static function post ($route, $callback) {
        static::match(['post'], $route, $callback);
    }

    // A wrapper function to match any route
    public static function any ($route, $callback) {
        static::match(['get', 'post'], $route, $callback);
    }

    // A function which handles the response return by the callback
    public static function handleResponse ($response) {
        // Stop running when nothing is returned
        if (is_null($response)) {
            exit;
        }

        // Echo and stop running when a string is returned
        if (is_string($response)) {
            echo $response;
            exit;
        }

        // Echo the json and stop when an array or object is returned
        if (is_array($response) || is_object($response)) {
            header('Content-Type: application/json');
            echo json_encode($response);
            exit;
        }
    }

    // A function which matches a route with the current route
    public static function match ($methods, $route, $callback) {
        // Remove trailing slashes from the request path
        $path = rtrim(preg_replace('#/+#', '/', strtok($_SERVER['REQUEST_URI'], '?')), '/');
        if ($path == '') $path = '/';

        // Check if the route is the same as the url
        if (
            in_array(strtolower($_SERVER['REQUEST_METHOD']), $methods) &&
            preg_match('#^' . preg_replace('/{.*}/U', '([^/]*)', $route) . '$#', $path, $values)
        ) {
            array_shift($values);

            // Call the callback
            static::handleResponse(call_user_func_array($callback, $values));
        }
    }

    // A function whichs is a fallback when all other routes didn't match can be used for a 404 page
    public static function fallback ($callback) {
        static::handleResponse(call_user_func($callback));
    }

    // A function that redirects to a specific route
    public static function redirect ($route) {
        header('Location: ' . $route);
        exit;
    }

    // A function that redirects page to the previous page
    public static function back () {
        static::redirect($_SERVER['HTTP_REFERER']);
    }
}

// Wrapper function to get GET or POST variables
function request ($key, $default = '') {
    return isset($_REQUEST[$key]) ? $_REQUEST[$key] : $default;
}

// Generate secure password
function generatePassword ($length) {
    $chars = 'ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789!@#$%^&*_=+-/';
    $chars_length = strlen($chars);
    $password = '';
    for ($i = 0; $i < $length; $i++) {
        $password .= substr($chars, rand(0, $chars_length), 1);
    }
    return $password;
}

// Load WarQuest functions
require_once '../config.inc';
require_once '../constants.inc';
require_once '../database.inc';
require_once '../general.inc';

// Set HTTP cross origin header
header('Access-Control-Allow-Origin: *');

// Connect to the database
warquest_db_connect($config['dbhost'], $config['dbuser'], $config['dbpass'], $config['dbname']);

// Home page
Router::any('/api', function () {
    return [
        'success' => true,
        'message' => 'WarQuest API documentation: https://bit.ly/3kKfgzH'
    ];
});

// Login and get player information
Router::any('/api/auth/login', function () {
    // Get the member id by username and password
    $username = request('username');
    $password = request('password');
    $player_id = warquest_db_member_pid($username, $password);

    // Check if account exists
    if ($player_id == 0) {
        return [
            'success' => false,
            'banned' => false,
            'message' => 'Wrong username and / or password'
        ];
    }

    // Check if player is not banned
    $player = warquest_db_player($player_id);
    if (warquest_db_query_pattern($player, PATTERN_BAN)) {
        return [
            'success' => false,
            'banned' => true,
            'message' => 'This player is banned'
        ];
    }

    // Else return player info
    $member = warquest_db_member($player_id);
    $member->password = $password;
    return [
        'success' => true,
        'message' => 'Player information loaded successfully',
        'member' => $member,
        'player' => $player
    ];
});

// Register a new random player
Router::any('/api/auth/register', function () {
    // Generate temp username and secure random password
    $username = 'player-' . time();
    $password = generatePassword(12);

    // Create member
    $player_id = warquest_db_member_insert($username, $password, '');

    // Change username to member id
    $username = 'player-' . $player_id;
    warquest_db_member_username_update($player_id, $username);

    // Create player
    warquest_db_player_insert($username, $player_id);
    warquest_db_skill_insert($player_id, 4);

    // Return player info
    $member = warquest_db_member($player_id);
    $member->password = $password;
    $player = warquest_db_player($player_id);
    return [
        'success' => true,
        'message' => 'Player successfully created',
        'member' => $member,
        'player' => $player
    ];
});

// Login and get players information
Router::any('/api/players', function () {
    $usernames = request('usernames', []);
    $passwords = request('passwords', []);

    $players = [];

    // Loop over usernames and passwords
    foreach ($usernames as $i => $username) {
        $password = $passwords[$i];

        // Get the member id by username and password
        $player_id = warquest_db_member_pid($username, $password);


        // Check if account exists
        if ($player_id == 0) {
            return [
                'success' => false,
                'banned' => false,
                'message' => 'Wrong username and / or password'
            ];
        }

        // Check if player is not banned
        $player = warquest_db_player($player_id);
        if (warquest_db_query_pattern($player, PATTERN_BAN)) {
            return [
                'success' => false,
                'banned' => true,
                'message' => 'One of the players is banned'
            ];
        }

        // Add player info to players array
        $member = warquest_db_member($player_id);
        $member->password = $password;
        $players[] = [
            'member' => $member,
            'player' => $player
        ];
    }

    // Return information when successfull
    return [
        'success' => true,
        'banned' => false,
        'message' => 'Players information loaded successfully',
        'players' => $players
    ];
});

// 404 Fallback page
Router::fallback(function () {
    http_response_code(404);
    return [
        'success' => false,
        'message' => '404 Not Found'
    ];
});
