/*
 * This file generated automatically from res.xml by c_client.py.
 * Edit at your peril.
 */

#ifdef HAVE_CONFIG_H
#  include "config.h"
#endif
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stddef.h>  /* for offsetof() */
#include "xcb/xcbext.h"
#include "xcb/res.h"

#define ALIGNOF(type)    \
    offsetof(            \
        struct {         \
            char dummy;  \
            type member; \
        },               \
        member)
#include "xcb/xproto.h"

xcb_extension_t xcb_res_id = { "X-Resource", 0 };

void
xcb_res_client_next(xcb_res_client_iterator_t *i)
{
    --i->rem;
    ++i->data;
    i->index += sizeof(xcb_res_client_t);
}

xcb_generic_iterator_t
xcb_res_client_end(xcb_res_client_iterator_t i)
{
    xcb_generic_iterator_t ret;
    ret.data  = i.data + i.rem;
    ret.index = i.index + ((char *)ret.data - (char *)i.data);
    ret.rem   = 0;
    return ret;
}

void
xcb_res_type_next(xcb_res_type_iterator_t *i)
{
    --i->rem;
    ++i->data;
    i->index += sizeof(xcb_res_type_t);
}

xcb_generic_iterator_t
xcb_res_type_end(xcb_res_type_iterator_t i)
{
    xcb_generic_iterator_t ret;
    ret.data  = i.data + i.rem;
    ret.index = i.index + ((char *)ret.data - (char *)i.data);
    ret.rem   = 0;
    return ret;
}

void
xcb_res_client_id_spec_next(xcb_res_client_id_spec_iterator_t *i)
{
    --i->rem;
    ++i->data;
    i->index += sizeof(xcb_res_client_id_spec_t);
}

xcb_generic_iterator_t
xcb_res_client_id_spec_end(xcb_res_client_id_spec_iterator_t i)
{
    xcb_generic_iterator_t ret;
    ret.data  = i.data + i.rem;
    ret.index = i.index + ((char *)ret.data - (char *)i.data);
    ret.rem   = 0;
    return ret;
}

int
xcb_res_client_id_value_sizeof(const void *_buffer)
{
    char                            *xcb_tmp = (char *)_buffer;
    const xcb_res_client_id_value_t *_aux =
        (xcb_res_client_id_value_t *)_buffer;
    unsigned int xcb_buffer_len = 0;
    unsigned int xcb_block_len  = 0;
    unsigned int xcb_pad        = 0;
    unsigned int xcb_align_to   = 0;

    xcb_block_len += sizeof(xcb_res_client_id_value_t);
    xcb_tmp += xcb_block_len;
    xcb_buffer_len += xcb_block_len;
    xcb_block_len = 0;
    /* value */
    xcb_block_len += (_aux->length / 4) * sizeof(uint32_t);
    xcb_tmp += xcb_block_len;
    xcb_align_to = ALIGNOF(uint32_t);
    /* insert padding */
    xcb_pad      = -xcb_block_len & (xcb_align_to - 1);
    xcb_buffer_len += xcb_block_len + xcb_pad;
    if (0 != xcb_pad)
    {
        xcb_tmp += xcb_pad;
        xcb_pad = 0;
    }
    xcb_block_len = 0;

    return xcb_buffer_len;
}

uint32_t *
xcb_res_client_id_value_value(const xcb_res_client_id_value_t *R)
{
    return (uint32_t *)(R + 1);
}

int
xcb_res_client_id_value_value_length(const xcb_res_client_id_value_t *R)
{
    return (R->length / 4);
}

xcb_generic_iterator_t
xcb_res_client_id_value_value_end(const xcb_res_client_id_value_t *R)
{
    xcb_generic_iterator_t i;
    i.data  = ((uint32_t *)(R + 1)) + ((R->length / 4));
    i.rem   = 0;
    i.index = (char *)i.data - (char *)R;
    return i;
}

void
xcb_res_client_id_value_next(xcb_res_client_id_value_iterator_t *i)
{
    xcb_res_client_id_value_t *R = i->data;
    xcb_generic_iterator_t     child;
    child.data =
        (xcb_res_client_id_value_t *)(((char *)R) +
                                      xcb_res_client_id_value_sizeof(R));
    i->index = (char *)child.data - (char *)i->data;
    --i->rem;
    i->data = (xcb_res_client_id_value_t *)child.data;
}

xcb_generic_iterator_t
xcb_res_client_id_value_end(xcb_res_client_id_value_iterator_t i)
{
    xcb_generic_iterator_t ret;
    while (i.rem > 0)
        xcb_res_client_id_value_next(&i);
    ret.data  = i.data;
    ret.rem   = i.rem;
    ret.index = i.index;
    return ret;
}

void
xcb_res_resource_id_spec_next(xcb_res_resource_id_spec_iterator_t *i)
{
    --i->rem;
    ++i->data;
    i->index += sizeof(xcb_res_resource_id_spec_t);
}

xcb_generic_iterator_t
xcb_res_resource_id_spec_end(xcb_res_resource_id_spec_iterator_t i)
{
    xcb_generic_iterator_t ret;
    ret.data  = i.data + i.rem;
    ret.index = i.index + ((char *)ret.data - (char *)i.data);
    ret.rem   = 0;
    return ret;
}

void
xcb_res_resource_size_spec_next(xcb_res_resource_size_spec_iterator_t *i)
{
    --i->rem;
    ++i->data;
    i->index += sizeof(xcb_res_resource_size_spec_t);
}

xcb_generic_iterator_t
xcb_res_resource_size_spec_end(xcb_res_resource_size_spec_iterator_t i)
{
    xcb_generic_iterator_t ret;
    ret.data  = i.data + i.rem;
    ret.index = i.index + ((char *)ret.data - (char *)i.data);
    ret.rem   = 0;
    return ret;
}

int
xcb_res_resource_size_value_sizeof(const void *_buffer)
{
    char                                *xcb_tmp = (char *)_buffer;
    const xcb_res_resource_size_value_t *_aux =
        (xcb_res_resource_size_value_t *)_buffer;
    unsigned int xcb_buffer_len = 0;
    unsigned int xcb_block_len  = 0;
    unsigned int xcb_pad        = 0;
    unsigned int xcb_align_to   = 0;

    xcb_block_len += sizeof(xcb_res_resource_size_value_t);
    xcb_tmp += xcb_block_len;
    xcb_buffer_len += xcb_block_len;
    xcb_block_len = 0;
    /* cross_references */
    xcb_block_len +=
        _aux->num_cross_references * sizeof(xcb_res_resource_size_spec_t);
    xcb_tmp += xcb_block_len;
    xcb_align_to = ALIGNOF(xcb_res_resource_size_spec_t);
    /* insert padding */
    xcb_pad      = -xcb_block_len & (xcb_align_to - 1);
    xcb_buffer_len += xcb_block_len + xcb_pad;
    if (0 != xcb_pad)
    {
        xcb_tmp += xcb_pad;
        xcb_pad = 0;
    }
    xcb_block_len = 0;

    return xcb_buffer_len;
}

xcb_res_resource_size_spec_t *
xcb_res_resource_size_value_cross_references(
    const xcb_res_resource_size_value_t *R)
{
    return (xcb_res_resource_size_spec_t *)(R + 1);
}

int
xcb_res_resource_size_value_cross_references_length(
    const xcb_res_resource_size_value_t *R)
{
    return R->num_cross_references;
}

xcb_res_resource_size_spec_iterator_t
xcb_res_resource_size_value_cross_references_iterator(
    const xcb_res_resource_size_value_t *R)
{
    xcb_res_resource_size_spec_iterator_t i;
    i.data  = (xcb_res_resource_size_spec_t *)(R + 1);
    i.rem   = R->num_cross_references;
    i.index = (char *)i.data - (char *)R;
    return i;
}

void
xcb_res_resource_size_value_next(xcb_res_resource_size_value_iterator_t *i)
{
    xcb_res_resource_size_value_t *R = i->data;
    xcb_generic_iterator_t         child;
    child.data =
        (xcb_res_resource_size_value_t *)(((char *)R) +
                                          xcb_res_resource_size_value_sizeof(
                                              R));
    i->index = (char *)child.data - (char *)i->data;
    --i->rem;
    i->data = (xcb_res_resource_size_value_t *)child.data;
}

xcb_generic_iterator_t
xcb_res_resource_size_value_end(xcb_res_resource_size_value_iterator_t i)
{
    xcb_generic_iterator_t ret;
    while (i.rem > 0)
        xcb_res_resource_size_value_next(&i);
    ret.data  = i.data;
    ret.rem   = i.rem;
    ret.index = i.index;
    return ret;
}

xcb_res_query_version_cookie_t
xcb_res_query_version(xcb_connection_t *c,
                      uint8_t           client_major,
                      uint8_t           client_minor)
{
    static const xcb_protocol_request_t xcb_req = { .count = 2,
                                                    .ext   = &xcb_res_id,
                                                    .opcode =
                                                        XCB_RES_QUERY_VERSION,
                                                    .isvoid = 0 };

    struct iovec                    xcb_parts[4];
    xcb_res_query_version_cookie_t  xcb_ret;
    xcb_res_query_version_request_t xcb_out;

    xcb_out.client_major = client_major;
    xcb_out.client_minor = client_minor;

    xcb_parts[2].iov_base = (char *)&xcb_out;
    xcb_parts[2].iov_len  = sizeof(xcb_out);
    xcb_parts[3].iov_base = 0;
    xcb_parts[3].iov_len  = -xcb_parts[2].iov_len & 3;

    xcb_ret.sequence =
        xcb_send_request(c, XCB_REQUEST_CHECKED, xcb_parts + 2, &xcb_req);
    return xcb_ret;
}

xcb_res_query_version_cookie_t
xcb_res_query_version_unchecked(xcb_connection_t *c,
                                uint8_t           client_major,
                                uint8_t           client_minor)
{
    static const xcb_protocol_request_t xcb_req = { .count = 2,
                                                    .ext   = &xcb_res_id,
                                                    .opcode =
                                                        XCB_RES_QUERY_VERSION,
                                                    .isvoid = 0 };

    struct iovec                    xcb_parts[4];
    xcb_res_query_version_cookie_t  xcb_ret;
    xcb_res_query_version_request_t xcb_out;

    xcb_out.client_major = client_major;
    xcb_out.client_minor = client_minor;

    xcb_parts[2].iov_base = (char *)&xcb_out;
    xcb_parts[2].iov_len  = sizeof(xcb_out);
    xcb_parts[3].iov_base = 0;
    xcb_parts[3].iov_len  = -xcb_parts[2].iov_len & 3;

    xcb_ret.sequence = xcb_send_request(c, 0, xcb_parts + 2, &xcb_req);
    return xcb_ret;
}

xcb_res_query_version_reply_t *
xcb_res_query_version_reply(xcb_connection_t              *c,
                            xcb_res_query_version_cookie_t cookie /**< */,
                            xcb_generic_error_t          **e)
{
    return (xcb_res_query_version_reply_t *)xcb_wait_for_reply(c,
                                                               cookie.sequence,
                                                               e);
}

int
xcb_res_query_clients_sizeof(const void *_buffer)
{
    char                                *xcb_tmp = (char *)_buffer;
    const xcb_res_query_clients_reply_t *_aux =
        (xcb_res_query_clients_reply_t *)_buffer;
    unsigned int xcb_buffer_len = 0;
    unsigned int xcb_block_len  = 0;
    unsigned int xcb_pad        = 0;
    unsigned int xcb_align_to   = 0;

    xcb_block_len += sizeof(xcb_res_query_clients_reply_t);
    xcb_tmp += xcb_block_len;
    xcb_buffer_len += xcb_block_len;
    xcb_block_len = 0;
    /* clients */
    xcb_block_len += _aux->num_clients * sizeof(xcb_res_client_t);
    xcb_tmp += xcb_block_len;
    xcb_align_to = ALIGNOF(xcb_res_client_t);
    /* insert padding */
    xcb_pad      = -xcb_block_len & (xcb_align_to - 1);
    xcb_buffer_len += xcb_block_len + xcb_pad;
    if (0 != xcb_pad)
    {
        xcb_tmp += xcb_pad;
        xcb_pad = 0;
    }
    xcb_block_len = 0;

    return xcb_buffer_len;
}

xcb_res_query_clients_cookie_t
xcb_res_query_clients(xcb_connection_t *c)
{
    static const xcb_protocol_request_t xcb_req = { .count = 2,
                                                    .ext   = &xcb_res_id,
                                                    .opcode =
                                                        XCB_RES_QUERY_CLIENTS,
                                                    .isvoid = 0 };

    struct iovec                    xcb_parts[4];
    xcb_res_query_clients_cookie_t  xcb_ret;
    xcb_res_query_clients_request_t xcb_out;

    xcb_parts[2].iov_base = (char *)&xcb_out;
    xcb_parts[2].iov_len  = sizeof(xcb_out);
    xcb_parts[3].iov_base = 0;
    xcb_parts[3].iov_len  = -xcb_parts[2].iov_len & 3;

    xcb_ret.sequence =
        xcb_send_request(c, XCB_REQUEST_CHECKED, xcb_parts + 2, &xcb_req);
    return xcb_ret;
}

xcb_res_query_clients_cookie_t
xcb_res_query_clients_unchecked(xcb_connection_t *c)
{
    static const xcb_protocol_request_t xcb_req = { .count = 2,
                                                    .ext   = &xcb_res_id,
                                                    .opcode =
                                                        XCB_RES_QUERY_CLIENTS,
                                                    .isvoid = 0 };

    struct iovec                    xcb_parts[4];
    xcb_res_query_clients_cookie_t  xcb_ret;
    xcb_res_query_clients_request_t xcb_out;

    xcb_parts[2].iov_base = (char *)&xcb_out;
    xcb_parts[2].iov_len  = sizeof(xcb_out);
    xcb_parts[3].iov_base = 0;
    xcb_parts[3].iov_len  = -xcb_parts[2].iov_len & 3;

    xcb_ret.sequence = xcb_send_request(c, 0, xcb_parts + 2, &xcb_req);
    return xcb_ret;
}

xcb_res_client_t *
xcb_res_query_clients_clients(const xcb_res_query_clients_reply_t *R)
{
    return (xcb_res_client_t *)(R + 1);
}

int
xcb_res_query_clients_clients_length(const xcb_res_query_clients_reply_t *R)
{
    return R->num_clients;
}

xcb_res_client_iterator_t
xcb_res_query_clients_clients_iterator(const xcb_res_query_clients_reply_t *R)
{
    xcb_res_client_iterator_t i;
    i.data  = (xcb_res_client_t *)(R + 1);
    i.rem   = R->num_clients;
    i.index = (char *)i.data - (char *)R;
    return i;
}

xcb_res_query_clients_reply_t *
xcb_res_query_clients_reply(xcb_connection_t              *c,
                            xcb_res_query_clients_cookie_t cookie /**< */,
                            xcb_generic_error_t          **e)
{
    return (xcb_res_query_clients_reply_t *)xcb_wait_for_reply(c,
                                                               cookie.sequence,
                                                               e);
}

int
xcb_res_query_client_resources_sizeof(const void *_buffer)
{
    char                                         *xcb_tmp = (char *)_buffer;
    const xcb_res_query_client_resources_reply_t *_aux =
        (xcb_res_query_client_resources_reply_t *)_buffer;
    unsigned int xcb_buffer_len = 0;
    unsigned int xcb_block_len  = 0;
    unsigned int xcb_pad        = 0;
    unsigned int xcb_align_to   = 0;

    xcb_block_len += sizeof(xcb_res_query_client_resources_reply_t);
    xcb_tmp += xcb_block_len;
    xcb_buffer_len += xcb_block_len;
    xcb_block_len = 0;
    /* types */
    xcb_block_len += _aux->num_types * sizeof(xcb_res_type_t);
    xcb_tmp += xcb_block_len;
    xcb_align_to = ALIGNOF(xcb_res_type_t);
    /* insert padding */
    xcb_pad      = -xcb_block_len & (xcb_align_to - 1);
    xcb_buffer_len += xcb_block_len + xcb_pad;
    if (0 != xcb_pad)
    {
        xcb_tmp += xcb_pad;
        xcb_pad = 0;
    }
    xcb_block_len = 0;

    return xcb_buffer_len;
}

xcb_res_query_client_resources_cookie_t
xcb_res_query_client_resources(xcb_connection_t *c, uint32_t xid)
{
    static const xcb_protocol_request_t xcb_req = {
        .count  = 2,
        .ext    = &xcb_res_id,
        .opcode = XCB_RES_QUERY_CLIENT_RESOURCES,
        .isvoid = 0
    };

    struct iovec                             xcb_parts[4];
    xcb_res_query_client_resources_cookie_t  xcb_ret;
    xcb_res_query_client_resources_request_t xcb_out;

    xcb_out.xid = xid;

    xcb_parts[2].iov_base = (char *)&xcb_out;
    xcb_parts[2].iov_len  = sizeof(xcb_out);
    xcb_parts[3].iov_base = 0;
    xcb_parts[3].iov_len  = -xcb_parts[2].iov_len & 3;

    xcb_ret.sequence =
        xcb_send_request(c, XCB_REQUEST_CHECKED, xcb_parts + 2, &xcb_req);
    return xcb_ret;
}

xcb_res_query_client_resources_cookie_t
xcb_res_query_client_resources_unchecked(xcb_connection_t *c, uint32_t xid)
{
    static const xcb_protocol_request_t xcb_req = {
        .count  = 2,
        .ext    = &xcb_res_id,
        .opcode = XCB_RES_QUERY_CLIENT_RESOURCES,
        .isvoid = 0
    };

    struct iovec                             xcb_parts[4];
    xcb_res_query_client_resources_cookie_t  xcb_ret;
    xcb_res_query_client_resources_request_t xcb_out;

    xcb_out.xid = xid;

    xcb_parts[2].iov_base = (char *)&xcb_out;
    xcb_parts[2].iov_len  = sizeof(xcb_out);
    xcb_parts[3].iov_base = 0;
    xcb_parts[3].iov_len  = -xcb_parts[2].iov_len & 3;

    xcb_ret.sequence = xcb_send_request(c, 0, xcb_parts + 2, &xcb_req);
    return xcb_ret;
}

xcb_res_type_t *
xcb_res_query_client_resources_types(
    const xcb_res_query_client_resources_reply_t *R)
{
    return (xcb_res_type_t *)(R + 1);
}

int
xcb_res_query_client_resources_types_length(
    const xcb_res_query_client_resources_reply_t *R)
{
    return R->num_types;
}

xcb_res_type_iterator_t
xcb_res_query_client_resources_types_iterator(
    const xcb_res_query_client_resources_reply_t *R)
{
    xcb_res_type_iterator_t i;
    i.data  = (xcb_res_type_t *)(R + 1);
    i.rem   = R->num_types;
    i.index = (char *)i.data - (char *)R;
    return i;
}

xcb_res_query_client_resources_reply_t *
xcb_res_query_client_resources_reply(
    xcb_connection_t                       *c,
    xcb_res_query_client_resources_cookie_t cookie /**< */,
    xcb_generic_error_t                   **e)
{
    return (xcb_res_query_client_resources_reply_t *)
        xcb_wait_for_reply(c, cookie.sequence, e);
}

xcb_res_query_client_pixmap_bytes_cookie_t
xcb_res_query_client_pixmap_bytes(xcb_connection_t *c, uint32_t xid)
{
    static const xcb_protocol_request_t xcb_req = {
        .count  = 2,
        .ext    = &xcb_res_id,
        .opcode = XCB_RES_QUERY_CLIENT_PIXMAP_BYTES,
        .isvoid = 0
    };

    struct iovec                                xcb_parts[4];
    xcb_res_query_client_pixmap_bytes_cookie_t  xcb_ret;
    xcb_res_query_client_pixmap_bytes_request_t xcb_out;

    xcb_out.xid = xid;

    xcb_parts[2].iov_base = (char *)&xcb_out;
    xcb_parts[2].iov_len  = sizeof(xcb_out);
    xcb_parts[3].iov_base = 0;
    xcb_parts[3].iov_len  = -xcb_parts[2].iov_len & 3;

    xcb_ret.sequence =
        xcb_send_request(c, XCB_REQUEST_CHECKED, xcb_parts + 2, &xcb_req);
    return xcb_ret;
}

xcb_res_query_client_pixmap_bytes_cookie_t
xcb_res_query_client_pixmap_bytes_unchecked(xcb_connection_t *c, uint32_t xid)
{
    static const xcb_protocol_request_t xcb_req = {
        .count  = 2,
        .ext    = &xcb_res_id,
        .opcode = XCB_RES_QUERY_CLIENT_PIXMAP_BYTES,
        .isvoid = 0
    };

    struct iovec                                xcb_parts[4];
    xcb_res_query_client_pixmap_bytes_cookie_t  xcb_ret;
    xcb_res_query_client_pixmap_bytes_request_t xcb_out;

    xcb_out.xid = xid;

    xcb_parts[2].iov_base = (char *)&xcb_out;
    xcb_parts[2].iov_len  = sizeof(xcb_out);
    xcb_parts[3].iov_base = 0;
    xcb_parts[3].iov_len  = -xcb_parts[2].iov_len & 3;

    xcb_ret.sequence = xcb_send_request(c, 0, xcb_parts + 2, &xcb_req);
    return xcb_ret;
}

xcb_res_query_client_pixmap_bytes_reply_t *
xcb_res_query_client_pixmap_bytes_reply(
    xcb_connection_t                          *c,
    xcb_res_query_client_pixmap_bytes_cookie_t cookie /**< */,
    xcb_generic_error_t                      **e)
{
    return (xcb_res_query_client_pixmap_bytes_reply_t *)
        xcb_wait_for_reply(c, cookie.sequence, e);
}

int
xcb_res_query_client_ids_sizeof(const void *_buffer)
{
    char                                     *xcb_tmp = (char *)_buffer;
    const xcb_res_query_client_ids_request_t *_aux =
        (xcb_res_query_client_ids_request_t *)_buffer;
    unsigned int xcb_buffer_len = 0;
    unsigned int xcb_block_len  = 0;
    unsigned int xcb_pad        = 0;
    unsigned int xcb_align_to   = 0;

    xcb_block_len += sizeof(xcb_res_query_client_ids_request_t);
    xcb_tmp += xcb_block_len;
    xcb_buffer_len += xcb_block_len;
    xcb_block_len = 0;
    /* specs */
    xcb_block_len += _aux->num_specs * sizeof(xcb_res_client_id_spec_t);
    xcb_tmp += xcb_block_len;
    xcb_align_to = ALIGNOF(xcb_res_client_id_spec_t);
    /* insert padding */
    xcb_pad      = -xcb_block_len & (xcb_align_to - 1);
    xcb_buffer_len += xcb_block_len + xcb_pad;
    if (0 != xcb_pad)
    {
        xcb_tmp += xcb_pad;
        xcb_pad = 0;
    }
    xcb_block_len = 0;

    return xcb_buffer_len;
}

xcb_res_query_client_ids_cookie_t
xcb_res_query_client_ids(xcb_connection_t               *c,
                         uint32_t                        num_specs,
                         const xcb_res_client_id_spec_t *specs)
{
    static const xcb_protocol_request_t xcb_req = {
        .count  = 4,
        .ext    = &xcb_res_id,
        .opcode = XCB_RES_QUERY_CLIENT_IDS,
        .isvoid = 0
    };

    struct iovec                       xcb_parts[6];
    xcb_res_query_client_ids_cookie_t  xcb_ret;
    xcb_res_query_client_ids_request_t xcb_out;

    xcb_out.num_specs = num_specs;

    xcb_parts[2].iov_base = (char *)&xcb_out;
    xcb_parts[2].iov_len  = sizeof(xcb_out);
    xcb_parts[3].iov_base = 0;
    xcb_parts[3].iov_len  = -xcb_parts[2].iov_len & 3;
    /* xcb_res_client_id_spec_t specs */
    xcb_parts[4].iov_base = (char *)specs;
    xcb_parts[4].iov_len  = num_specs * sizeof(xcb_res_client_id_spec_t);
    xcb_parts[5].iov_base = 0;
    xcb_parts[5].iov_len  = -xcb_parts[4].iov_len & 3;

    xcb_ret.sequence =
        xcb_send_request(c, XCB_REQUEST_CHECKED, xcb_parts + 2, &xcb_req);
    return xcb_ret;
}

xcb_res_query_client_ids_cookie_t
xcb_res_query_client_ids_unchecked(xcb_connection_t               *c,
                                   uint32_t                        num_specs,
                                   const xcb_res_client_id_spec_t *specs)
{
    static const xcb_protocol_request_t xcb_req = {
        .count  = 4,
        .ext    = &xcb_res_id,
        .opcode = XCB_RES_QUERY_CLIENT_IDS,
        .isvoid = 0
    };

    struct iovec                       xcb_parts[6];
    xcb_res_query_client_ids_cookie_t  xcb_ret;
    xcb_res_query_client_ids_request_t xcb_out;

    xcb_out.num_specs = num_specs;

    xcb_parts[2].iov_base = (char *)&xcb_out;
    xcb_parts[2].iov_len  = sizeof(xcb_out);
    xcb_parts[3].iov_base = 0;
    xcb_parts[3].iov_len  = -xcb_parts[2].iov_len & 3;
    /* xcb_res_client_id_spec_t specs */
    xcb_parts[4].iov_base = (char *)specs;
    xcb_parts[4].iov_len  = num_specs * sizeof(xcb_res_client_id_spec_t);
    xcb_parts[5].iov_base = 0;
    xcb_parts[5].iov_len  = -xcb_parts[4].iov_len & 3;

    xcb_ret.sequence = xcb_send_request(c, 0, xcb_parts + 2, &xcb_req);
    return xcb_ret;
}

int
xcb_res_query_client_ids_ids_length(const xcb_res_query_client_ids_reply_t *R)
{
    return R->num_ids;
}

xcb_res_client_id_value_iterator_t
xcb_res_query_client_ids_ids_iterator(const xcb_res_query_client_ids_reply_t *R)
{
    xcb_res_client_id_value_iterator_t i;
    i.data  = (xcb_res_client_id_value_t *)(R + 1);
    i.rem   = R->num_ids;
    i.index = (char *)i.data - (char *)R;
    return i;
}

xcb_res_query_client_ids_reply_t *
xcb_res_query_client_ids_reply(xcb_connection_t                 *c,
                               xcb_res_query_client_ids_cookie_t cookie /**< */,
                               xcb_generic_error_t             **e)
{
    return (xcb_res_query_client_ids_reply_t *)
        xcb_wait_for_reply(c, cookie.sequence, e);
}

int
xcb_res_query_resource_bytes_sizeof(const void *_buffer)
{
    char                                         *xcb_tmp = (char *)_buffer;
    const xcb_res_query_resource_bytes_request_t *_aux =
        (xcb_res_query_resource_bytes_request_t *)_buffer;
    unsigned int xcb_buffer_len = 0;
    unsigned int xcb_block_len  = 0;
    unsigned int xcb_pad        = 0;
    unsigned int xcb_align_to   = 0;

    xcb_block_len += sizeof(xcb_res_query_resource_bytes_request_t);
    xcb_tmp += xcb_block_len;
    xcb_buffer_len += xcb_block_len;
    xcb_block_len = 0;
    /* specs */
    xcb_block_len += _aux->num_specs * sizeof(xcb_res_resource_id_spec_t);
    xcb_tmp += xcb_block_len;
    xcb_align_to = ALIGNOF(xcb_res_resource_id_spec_t);
    /* insert padding */
    xcb_pad      = -xcb_block_len & (xcb_align_to - 1);
    xcb_buffer_len += xcb_block_len + xcb_pad;
    if (0 != xcb_pad)
    {
        xcb_tmp += xcb_pad;
        xcb_pad = 0;
    }
    xcb_block_len = 0;

    return xcb_buffer_len;
}

xcb_res_query_resource_bytes_cookie_t
xcb_res_query_resource_bytes(xcb_connection_t                 *c,
                             uint32_t                          client,
                             uint32_t                          num_specs,
                             const xcb_res_resource_id_spec_t *specs)
{
    static const xcb_protocol_request_t xcb_req = {
        .count  = 4,
        .ext    = &xcb_res_id,
        .opcode = XCB_RES_QUERY_RESOURCE_BYTES,
        .isvoid = 0
    };

    struct iovec                           xcb_parts[6];
    xcb_res_query_resource_bytes_cookie_t  xcb_ret;
    xcb_res_query_resource_bytes_request_t xcb_out;

    xcb_out.client    = client;
    xcb_out.num_specs = num_specs;

    xcb_parts[2].iov_base = (char *)&xcb_out;
    xcb_parts[2].iov_len  = sizeof(xcb_out);
    xcb_parts[3].iov_base = 0;
    xcb_parts[3].iov_len  = -xcb_parts[2].iov_len & 3;
    /* xcb_res_resource_id_spec_t specs */
    xcb_parts[4].iov_base = (char *)specs;
    xcb_parts[4].iov_len  = num_specs * sizeof(xcb_res_resource_id_spec_t);
    xcb_parts[5].iov_base = 0;
    xcb_parts[5].iov_len  = -xcb_parts[4].iov_len & 3;

    xcb_ret.sequence =
        xcb_send_request(c, XCB_REQUEST_CHECKED, xcb_parts + 2, &xcb_req);
    return xcb_ret;
}

xcb_res_query_resource_bytes_cookie_t
xcb_res_query_resource_bytes_unchecked(xcb_connection_t *c,
                                       uint32_t          client,
                                       uint32_t          num_specs,
                                       const xcb_res_resource_id_spec_t *specs)
{
    static const xcb_protocol_request_t xcb_req = {
        .count  = 4,
        .ext    = &xcb_res_id,
        .opcode = XCB_RES_QUERY_RESOURCE_BYTES,
        .isvoid = 0
    };

    struct iovec                           xcb_parts[6];
    xcb_res_query_resource_bytes_cookie_t  xcb_ret;
    xcb_res_query_resource_bytes_request_t xcb_out;

    xcb_out.client    = client;
    xcb_out.num_specs = num_specs;

    xcb_parts[2].iov_base = (char *)&xcb_out;
    xcb_parts[2].iov_len  = sizeof(xcb_out);
    xcb_parts[3].iov_base = 0;
    xcb_parts[3].iov_len  = -xcb_parts[2].iov_len & 3;
    /* xcb_res_resource_id_spec_t specs */
    xcb_parts[4].iov_base = (char *)specs;
    xcb_parts[4].iov_len  = num_specs * sizeof(xcb_res_resource_id_spec_t);
    xcb_parts[5].iov_base = 0;
    xcb_parts[5].iov_len  = -xcb_parts[4].iov_len & 3;

    xcb_ret.sequence = xcb_send_request(c, 0, xcb_parts + 2, &xcb_req);
    return xcb_ret;
}

int
xcb_res_query_resource_bytes_sizes_length(
    const xcb_res_query_resource_bytes_reply_t *R)
{
    return R->num_sizes;
}

xcb_res_resource_size_value_iterator_t
xcb_res_query_resource_bytes_sizes_iterator(
    const xcb_res_query_resource_bytes_reply_t *R)
{
    xcb_res_resource_size_value_iterator_t i;
    i.data  = (xcb_res_resource_size_value_t *)(R + 1);
    i.rem   = R->num_sizes;
    i.index = (char *)i.data - (char *)R;
    return i;
}

xcb_res_query_resource_bytes_reply_t *
xcb_res_query_resource_bytes_reply(
    xcb_connection_t                     *c,
    xcb_res_query_resource_bytes_cookie_t cookie /**< */,
    xcb_generic_error_t                 **e)
{
    return (xcb_res_query_resource_bytes_reply_t *)
        xcb_wait_for_reply(c, cookie.sequence, e);
}
