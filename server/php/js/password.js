// /*
// **  ========
// **  WarQuest
// **  ========
// **
// **  Created by wplaat
// **
// **  For more information visit the following website.
// **  Website : www.plaatsoft.nl
// **
// **  Or send an email to the following address.
// **  Email   : info@plaatsoft.nl
// **
// **  All copyrights reserved (c) PlaatSoft
// */

function scorePassword(pass) {
    var score = 0;
    if (!pass)
        return score;

    // award every unique letter until 5 repetitions
    var letters = new Object();
    for (var i=0; i<pass.length; i++) {
        letters[pass[i]] = (letters[pass[i]] || 0) + 1;
        score += 5.0 / letters[pass[i]];
    }

    // bonus points for mixing it up
    var variations = {
        digits: /\d/.test(pass),
        lower: /[a-z]/.test(pass),
        upper: /[A-Z]/.test(pass),
        nonWords: /\W/.test(pass),
    }

    variationCount = 0;
    for (var check in variations) {
        variationCount += (variations[check] == true) ? 1 : 0;
    }
    score += (variationCount - 1) * 10;

    return parseInt(score);
}

var passwordElement = document.getElementById('mypassword');
var passwordStrengthBarElement = document.getElementById('password-strength-bar');

passwordElement.oninput = function () {
    var score = scorePassword(passwordElement.value);
    if (score >= 80) {
        passwordStrengthBarElement.className = 'strong';
        passwordStrengthBarElement.style.width = '100%';
    }
    else if (score >= 60) {
        passwordStrengthBarElement.className = 'medium';
        passwordStrengthBarElement.style.width = '75%';
    }
    else if (score >= 30) {
        passwordStrengthBarElement.className = 'weak';
        passwordStrengthBarElement.style.width = '50%';
    }
    else {
        passwordStrengthBarElement.className = 'useless';
        passwordStrengthBarElement.style.width = '25%';
    }
};
