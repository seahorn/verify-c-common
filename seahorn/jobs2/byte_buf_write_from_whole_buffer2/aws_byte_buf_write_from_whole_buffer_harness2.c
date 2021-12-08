/*
 *
 */

#include <seahorn/seahorn.h>
#include <aws/common/byte_buf.h>
#include <byte_buf_helper.h>
#include <utils.h>

int main()
{
    /* parameters */
    struct aws_byte_buf buf;
    initialize_byte_buf(&buf);
    struct aws_byte_buf src;
    initialize_byte_buf(&src);

    /* assumptions */
    assume(aws_byte_buf_is_valid(&buf));
    assume(aws_byte_buf_is_valid(&src));

    /* save current state of the parameters */
    size_t buf_old_len = buf.len;
    size_t buf_old_capacity = buf.capacity;
    sea_tracking_on();

    /* operation under verification */
    if (aws_byte_buf_write_from_whole_buffer(&buf, src))
    {
        sassert(buf.len == buf_old_len + src.len);
        sassert(buf.capacity == buf_old_capacity);
        if (src.len > 0 && buf.len > 0)
        {
            assert_bytes_match(buf.buffer + buf_old_len, src.buffer, src.len);
        }
    }
    else
    {
        sassert(!sea_is_modified((char *)&buf));
        sassert(!sea_is_modified((char *)buf.buffer));
    }

    sassert(aws_byte_buf_is_valid(&buf));
    sassert(aws_byte_buf_is_valid(&src));

    sassert(!sea_is_modified((char *)buf.allocator));
    
    sassert(!sea_is_modified((char *)&src));
    sassert(!sea_is_modified((char *)src.buffer));
    sassert(!sea_is_modified((char *)src.allocator));

    return 0;
}
