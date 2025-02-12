/*
 * Copyright (c) 2022, Tobias Christiansen <tobyase@serenityos.org>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include "Cookie.h"
#include <LibIPC/Decoder.h>
#include <LibIPC/Encoder.h>

namespace Web::Cookie {

StringView same_site_to_string(SameSite same_site)
{
    switch (same_site) {
    case SameSite::Default:
        return "Default"sv;
    case SameSite::None:
        return "None"sv;
    case SameSite::Lax:
        return "Lax"sv;
    case SameSite::Strict:
        return "Strict"sv;
    }
    VERIFY_NOT_REACHED();
}

SameSite same_site_from_string(StringView same_site_mode)
{
    if (same_site_mode.equals_ignoring_case("None"sv))
        return SameSite::None;
    if (same_site_mode.equals_ignoring_case("Strict"sv))
        return SameSite::Strict;
    if (same_site_mode.equals_ignoring_case("Lax"sv))
        return SameSite::Lax;
    return SameSite::Default;
}

}

template<>
bool IPC::encode(Encoder& encoder, Web::Cookie::Cookie const& cookie)
{
    encoder << cookie.name;
    encoder << cookie.value;
    encoder << cookie.domain;
    encoder << cookie.path;
    encoder << cookie.creation_time;
    encoder << cookie.expiry_time;
    encoder << cookie.host_only;
    encoder << cookie.http_only;
    encoder << cookie.last_access_time;
    encoder << cookie.persistent;
    encoder << cookie.secure;
    encoder << cookie.same_site;

    return true;
}

template<>
ErrorOr<void> IPC::decode(Decoder& decoder, Web::Cookie::Cookie& cookie)
{
    TRY(decoder.decode(cookie.name));
    TRY(decoder.decode(cookie.value));
    TRY(decoder.decode(cookie.domain));
    TRY(decoder.decode(cookie.path));
    TRY(decoder.decode(cookie.creation_time));
    TRY(decoder.decode(cookie.expiry_time));
    TRY(decoder.decode(cookie.host_only));
    TRY(decoder.decode(cookie.http_only));
    TRY(decoder.decode(cookie.last_access_time));
    TRY(decoder.decode(cookie.persistent));
    TRY(decoder.decode(cookie.secure));
    TRY(decoder.decode(cookie.same_site));
    return {};
}
