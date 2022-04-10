# include "filter.h"


// fonction de filtrage par convolution
void Filter::filter()
{
    // r�solution du kernel de convolution
    const int kernel_size = 3;

    // d�calage � partir du centre du kernel
    const int kernel_offset = kernel_size / 2;

    // nombre de composantes de couleur (RGB)
    const int color_component_count = 3;

    // indices de l'image
    int x, y;

    // indices du kernel
    int i, j;

    // index des composantes de couleur
    int c;

    // index du pixel de l'image source utilis� pour le filtrage
    int pixel_index_img_src;

    // index du pixel de l'image de destination en cours de filtrage
    int pixel_index_img_dst;

    // index du pixel de l'image de destination en cours de filtrage
    int kernel_index;

    // valeur � un des indices du kernel de convolution
    float kernel_value;

    // extraire les pixels de l'image source
    ofPixels pixel_array_src = image_source.getPixels();

    // extraire les pixels de l'image de destination
    ofPixels pixel_array_dst = image_destination.getPixels();

    // ofPixels pixel_array_dst = image_destination.getPixels();


     // couleur du pixel lu dans l'image source
    ofColor pixel_color_src;

    // couleur du pixel � �crire dans l'image de destination
    ofColor pixel_color_dst;

    // somme du kernel appliqu�e � chaque composante de couleur d'un pixel
    float sum[color_component_count];

    // it�ration sur les rang�es des pixels de l'image source
    for (y = 0; y < image_height; ++y)
    {
        // it�ration sur les colonnes des pixels de l'image source
        for (x = 0; x < image_width; ++x)
        {
            // initialiser le tableau o� les valeurs de filtrage sont accumul�es
            for (c = 0; c < color_component_count; ++c)
                sum[c] = 0;

            // d�terminer l'index du pixel de l'image de destination
            pixel_index_img_dst = (image_width * y + x) * color_component_count;

            // it�ration sur les colonnes du kernel de convolution
            for (j = -kernel_offset; j <= kernel_offset; ++j)
            {
                // it�ration sur les rang�es du kernel de convolution
                for (i = -kernel_offset; i <= kernel_offset; ++i)
                {
                    // d�terminer l'index du pixel de l'image source � lire
                    pixel_index_img_src = (image_width * (y - j) + (x - i)) * color_component_count;

                    // lire la couleur du pixel de l'image source
                    pixel_color_src = pixel_array_src.getColor(pixel_index_img_src);

                    // d�terminer l'indice du facteur � lire dans le kernel de convolution
                    kernel_index = kernel_size * (j + kernel_offset) + (i + kernel_offset);

                    // extraction de la valeur � cet index du kernel
                    switch (kernel_type)
                    {
                    case ConvolutionKernel::identity:
                        kernel_value = convolution_kernel_identity.at(kernel_index);
                        break;

                    case ConvolutionKernel::emboss:
                        kernel_value = convolution_kernel_emboss.at(kernel_index);
                        break;

                    case ConvolutionKernel::sharpen:
                        kernel_value = convolution_kernel_sharpen.at(kernel_index);
                        break;

                    case ConvolutionKernel::edge_detect:
                        kernel_value = convolution_kernel_edge_detect.at(kernel_index);
                        break;

                    case ConvolutionKernel::blur:
                        kernel_value = convolution_kernel_blur.at(kernel_index);
                        break;

                    default:
                        kernel_value = convolution_kernel_identity.at(kernel_index);
                        break;
                    }

                    // it�ration sur les composantes de couleur
                    for (c = 0; c < color_component_count; ++c)
                    {
                        // accumuler les valeurs de filtrage en fonction du kernel de convolution
                        sum[c] = sum[c] + kernel_value * pixel_color_src[c];
                    }
                }
            }

            // d�terminer la couleur du pixel � partir des valeurs de filtrage accumul�es pour chaque composante
            for (c = 0; c < color_component_count; ++c)
            {
                // conversion vers entier et validation des bornes de l'espace de couleur
                pixel_color_dst[c] = (int)ofClamp(sum[c], 0, 255);
            }

            // �crire la couleur � l'index du pixel en cours de filtrage
            pixel_array_dst.setColor(pixel_index_img_dst, pixel_color_dst);
        }
    }

    // �crire les pixels dans l'image de destination
    if (kernel_name == "bosseler")
        image_destination.setFromPixels(pixel_array_dst);

    if (kernel_name == "aiguiser")
        image_destination2.setFromPixels(pixel_array_dst);

    if (kernel_name == "d�tection de bordure")
        image_destination3.setFromPixels(pixel_array_dst);


    ofLog() << "<convolution filter done>";
}