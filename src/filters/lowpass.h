float lowPassFilter(const float input, const float output, const float alpha)
{
    return output + alpha * (input - output);
}