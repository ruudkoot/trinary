void u16toa (unt16 value, char *string, unt8 radix)
{
        char *i, *s, t, d;

        s = i = string;

        do
        {   d = value % radix;
            value /= radix;

            if (d > 9)
                *i++ = d + 'A' - 10;
            else
                *i++ = d + '0';
        } while (value > 0);

        *i-- = '\0';

        do 
        {   t = *i;
            *i = *s;
            *s = t;

            --i;
            ++s;
        } while (s < i);
}
