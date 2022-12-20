package site.kalocsanyi;

import java.io.BufferedInputStream;

import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import fr.delthas.javamp3.Sound;

public class DiscreteFourierTransform {
    byte[] getSamples() throws IOException {
        Path audiopath = Paths.get("/home/ujoimro/Inst/mozillaaudio/cv-corpus-7.0-singleword/en/clips/common_voice_en_22140642.mp3");
        try (Sound sample_sound = new Sound(new BufferedInputStream(Files.newInputStream(audiopath)))) {
            System.out.println(sample_sound.getSamplingFrequency());
            byte[] samples = sample_sound.readAllBytes();
            return samples;
        }
    }

    // public static double[] toDouble2(byte[] b){
    // return Double.longBitsToDouble(bytesToLong(b)); //it's working if we
    // implement the bytestoLong function
    // }
    public static double[] toDouble(byte[] byte_array) throws IOException {
        // Path audiopath = Paths.get("/home/ujoimro/Inst/mozillaaudio/cv-corpus-7.0-singleword/en/clips/common_voice_en_22140642.mp3");
        // Sound sample_sound = new Sound(new
        // BufferedInputStream(Files.newInputStream(audiopath)));
        // System.out.println(sample_sound.getSamplingFrequency());
        // double[] darray = new double[byte_array.length/2];
        double[] darray = new double[byte_array.length / 2]; // need to make sure we are going through the whole array
        for (int dNum = 0; dNum < darray.length / 2; dNum++) {
            darray[dNum] = byte_array[2 * dNum] + byte_array[2 * dNum + 1] << 8; // Start with the integer = 0
        }
        return darray;
    }

    public double[] getDoubleSamples() throws IOException {
        Path audiopath = Paths.get("/home/ujoimro/Inst/mozillaaudio/cv-corpus-7.0-singleword/en/clips/common_voice_en_22140642.mp3");
        try (Sound sample_sound = new Sound(new BufferedInputStream(Files.newInputStream(audiopath)))) {
            System.out.println(sample_sound.getSamplingFrequency());
            byte[] samples = sample_sound.readAllBytes();
            double[] dsamples = toDouble(samples);
            return dsamples;
        }
    }

    public double[] Transform() throws IOException {
        // Path audiopath = Paths.get("/home/ujoimro/Inst/mozillaaudio/cv-corpus-7.0-singleword/en/clips/common_voice_en_22140642.mp3");
        // byte[] bsamples = getSamples();
        double[] dsamples = getDoubleSamples();
        var fourier = new site.kalocsanyi.DiscreteFourier(dsamples);
        fourier.transform();
        boolean onlyPositive = true;
        double[] out = fourier.getMagnitude(onlyPositive);
        return out;
    }
}